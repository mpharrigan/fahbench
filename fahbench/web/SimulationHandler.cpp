#include "SimulationHandler.h"

#include "../Simulation.h"
#include "WebUpdater.h"
#include "../WorkUnit.h"

#include <iostream>
#include <thread>

namespace http {
namespace server {


void SimulationHandler::handle_api(vector<string>::const_iterator begin, vector<string>::const_iterator end,
                                   pt::ptree & tree) {

    Simulation sim;
    std::cout << sim.summary() << std::endl;
    t = std::thread(&Simulation::run, sim, std::ref(*_web_updater));
    std::cout << "Launched thread I think\n";

}

SimulationHandler::SimulationHandler() {
    _web_updater = new WebUpdater();
}


}
}

