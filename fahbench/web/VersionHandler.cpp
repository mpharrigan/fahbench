#include "VersionHandler.h"

#include <iostream>

#include "../FAHBenchVersion.h"

namespace pt = boost::property_tree;

namespace http {
namespace server {

void VersionHandler::handle_api(vector< string >::const_iterator  begin, vector< string >::const_iterator  end, pt::ptree & tree) {
    for (auto & s = begin; s != end; ++s) {
        std::cout << "Part " << *s << std::endl;
    }

    tree.put("fahbench.major", FAHBench_VERSION_MAJOR);
    tree.put("fahbench.minor", FAHBench_VERSION_MINOR);
    tree.put("fahbench.revis", FAHBench_VERSION_REVIS);
    tree.put("fahbench.refspec", FAHBench_VERSION_REFSPEC);
    tree.put("fahbench.sha", FAHBench_VERSION_SHA);
    tree.put("fahbench.version_string", getVersion());
    tree.put("openmm", getOpenMMVersion());
}


}
}