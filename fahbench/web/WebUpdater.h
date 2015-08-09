//
// Created by harrigan on 8/9/15.
//

#ifndef FAHBENCH_WEBUPDATER_H
#define FAHBENCH_WEBUPDATER_H

#include "../Updater.h"


class WebUpdater : public Updater {

public:
    void progress(int step, int total_step, float score) override;

    void message(std::string string) override;

    void message(boost::format format) override;
};


#endif //FAHBENCH_WEBUPDATER_H
