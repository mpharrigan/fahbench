#ifndef FAHBENCH_SIMULATIONHANDLER_H
#define FAHBENCH_SIMULATIONHANDLER_H

#include <thread>

#include "../Simulation.h"
#include "WebUpdater.h"

#include "ApiHandler.h"

namespace http {
namespace server {

using std::vector;
using std::string;
namespace pt = boost::property_tree;

class SimulationHandler : public ApiHandler {

private:
    WebUpdater * _web_updater;
    std::thread t;


public:
    explicit SimulationHandler();
    virtual void handle_api(vector<string>::const_iterator begin, vector<string>::const_iterator end, pt::ptree & tree);
};

}
}

#endif //FAHBENCH_SIMULATIONHANDLER_H
