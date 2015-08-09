//
// Created by harrigan on 8/9/15.
//

#include "WebUpdater.h"

#include <iostream>

void WebUpdater::progress(int step, int total_step, float score) {
    std::cout << "progress " << step << " " << total_step << " " << score << std::endl;

}

void WebUpdater::message(std::string string) {
    std::lock_guard<std::mutex> lock(msg_mutex);
    messages.push_back(string);
    std::cout << "message " << string << std::endl;
}

void WebUpdater::message(boost::format format) {
    message(format.str());
}

WebUpdater::WebUpdater()
    : msg_mutex()
    , messages {"FAHBench initialized."}

{

}

void WebUpdater::status_json(pt::ptree & tree) {
    std::lock_guard<std::mutex> lock(msg_mutex);
    pt::ptree msgs_tree;
    for (auto const & msg : messages) {
        pt::ptree msg_tree;
        msg_tree.put("message", msg);
        msgs_tree.push_back(std::make_pair("", msg_tree));
    }
    tree.add_child("messages", msgs_tree);
    tree.put("status.current", 0);
    tree.put("status.total", 1);
    tree.put("status.score", 22.0);

}
