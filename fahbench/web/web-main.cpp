//
// main.cpp
// ~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Modified by Matthew Harrigan for use in FAHBench

#include <iostream>
#include <string>
#include <boost/asio.hpp>

#include "server/server.hpp"
#include "../Utils.h"

int main(int argc, char * argv[]) {
    try {
        // Check command line arguments.
        if (argc != 2) {
            std::cerr << "Usage: FAHBench-web <port>\n";
            return 1;
        }

        // Initialise the server.
        auto app_dir = (getExecutableDir() / ".." / "app/").string();
        std::cout << "Starting server on localhost port " << argv[1] << std::endl;
        std::cout << "Serving files from " << app_dir << std::endl;
        http::server::server s("0.0.0.0", argv[1], app_dir);

        // Run the server until stopped.
        s.run();
    } catch (std::exception & e) {
        std::cerr << "exception: " << e.what() << "\n";
    }

    return 0;
}
