//
// request_handler.cpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Modified by Matthew Harrigan for use in FAHBench-web

#include "request_handler.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include "server/mime_types.hpp"
#include "server/reply.hpp"
#include "server/request.hpp"

#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>



#include "VersionHandler.h"
#include "DeviceHandler.h"
#include "DefaultHandler.h"

namespace http {
namespace server {

namespace ba = boost::algorithm;
namespace pt = boost::property_tree;


request_handler::request_handler(const std::string & doc_root)
    : doc_root_(doc_root)
    , handlers_ {
    {"version", new VersionHandler()},
    {"devices", new DeviceHandler()},
    {"default", new DefaultHandler()}
}

{}


void request_handler::handle_file_request(const std::string & request_path, reply & rep) {
    std::cout << "Serving a file - ";

    // Determine the file extension.
    std::size_t last_slash_pos = request_path.find_last_of("/");
    std::size_t last_dot_pos = request_path.find_last_of(".");
    std::string extension;
    if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos) {
        extension = request_path.substr(last_dot_pos + 1);
    }

    // Open the file to send back.
    std::string full_path = doc_root_ + request_path;
    std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
    if (!is) {
        std::cout << "Couldn't find " << full_path << std::endl;
        rep = reply::stock_reply(reply::not_found);
        return;
    }
    std::cout << "Found " << full_path << std::endl;

    // Fill out the reply to be sent to the client.
    rep.status = reply::ok;
    char buf[512];
    while (is.read(buf, sizeof(buf)).gcount() > 0)
        rep.content.append(buf, is.gcount());
    rep.headers.resize(2);
    rep.headers[0].name = "Content-Length";
    rep.headers[0].value = std::to_string(rep.content.size());
    rep.headers[1].name = "Content-Type";
    rep.headers[1].value = mime_types::extension_to_type(extension);
}

void request_handler::handle_rest_request(const std::string & request_path, reply & rep) {
    std::cout << "Handling API call - ";

    std::vector<std::string> parts;
    ba::split(parts, request_path, ba::is_any_of("/"));

    if (parts[0] != "" || parts[1] != "api") {
        rep = reply::stock_reply(reply::not_found);
        return;
    }

    pt::ptree tree;

    auto lookup = parts[2];
    if (handlers_.count(lookup) == 0) {
        lookup = "default";
    }
    auto handle = handlers_.at(lookup);
    handle->handle_api(parts.begin() + 2, parts.cend(), tree);

    rep.status = reply::ok;
    std::stringstream content_ss;
    pt::json_parser::write_json<pt::ptree>(content_ss, tree);
    rep.content = content_ss.str();
    rep.headers.resize(2);
    rep.headers[0].name = "Content-Length";
    rep.headers[0].value = std::to_string(rep.content.size());
    rep.headers[1].name = "Content-Type";
    rep.headers[1].value = "application/json";
}


void request_handler::handle_request(const request & req, reply & rep) {
    std::cout << "Handling request " << req.uri << std::endl;

    // Decode url to path.
    std::string request_path;
    if (!url_decode(req.uri, request_path)) {
        rep = reply::stock_reply(reply::bad_request);
        return;
    }

    // Request path must be absolute and not contain "..".
    if (request_path.empty() || request_path[0] != '/'
            || ba::contains(request_path, "..")) {
        rep = reply::stock_reply(reply::bad_request);
        return;
    }

    if (ba::starts_with(request_path, "/api/")) {
        handle_rest_request(request_path, rep);
    } else {
        handle_file_request(request_path, rep);
    }


}

bool request_handler::url_decode(const std::string & in, std::string & out) {
    out.clear();
    out.reserve(in.size());
    for (std::size_t i = 0; i < in.size(); ++i) {
        if (in[i] == '%') {
            if (i + 3 <= in.size()) {
                int value = 0;
                std::istringstream is(in.substr(i + 1, 2));
                if (is >> std::hex >> value) {
                    out += static_cast<char>(value);
                    i += 2;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else if (in[i] == '+') {
            out += ' ';
        } else {
            out += in[i];
        }
    }
    return true;
}

request_handler::~request_handler() {
    std::cout << "Cleaning up handlers" << std::endl;
    for (auto & it : handlers_) {
        delete(it.second);
    }
}


} // namespace server
} // namespace http
