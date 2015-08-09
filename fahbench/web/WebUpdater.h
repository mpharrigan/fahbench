//
// Created by harrigan on 8/9/15.
//

#ifndef FAHBENCH_WEBUPDATER_H
#define FAHBENCH_WEBUPDATER_H

#include <mutex>

#include <boost/property_tree/ptree.hpp>

#include "../Updater.h"

namespace pt = boost::property_tree;

class WebUpdater : public Updater {

private:
    std::mutex msg_mutex;
    std::vector<std::string> messages;

public:
    explicit WebUpdater();

    void progress(int step, int total_step, float score) override;

    void message(std::string string) override;

    void message(boost::format format) override;

    void status_json(pt::ptree & tree);
};


#endif //FAHBENCH_WEBUPDATER_H
