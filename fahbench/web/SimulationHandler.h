#ifndef FAHBENCH_SIMULATIONHANDLER_H
#define FAHBENCH_SIMULATIONHANDLER_H

#include "ApiHandler.h"

namespace http {
namespace server {

using std::vector;
using std::string;
namespace pt = boost::property_tree;

class SimulationHandler : public ApiHandler {


public:
    virtual void handle_api(vector<string>::const_iterator begin, vector<string>::const_iterator end, pt::ptree & tree);
};

}
}

#endif //FAHBENCH_SIMULATIONHANDLER_H
