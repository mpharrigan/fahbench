//
// Created by harrigan on 8/9/15.
//

#include "WebUpdater.h"

#include <iostream>

void WebUpdater::progress(int step, int total_step, float score) {
    std::cout << "progress " << step << " " << total_step << " " << score << std::endl;

}

void WebUpdater::message(std::string string) {
    std::cout << "message " << string << std::endl;

}

void WebUpdater::message(boost::format format) {
    std::cout << "BMessage " << format << std::endl;
}
