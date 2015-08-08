#include "VersionHandler.h"

#include <iostream>



namespace pt = boost::property_tree;

namespace http {
namespace server {

void VersionHandler::handle_api(vector< string >::const_iterator  begin, vector< string >::const_iterator  end, pt::ptree & tree) {
    for (auto & s = begin; s != end; ++s) {
        std::cout << "Part " << *s << std::endl;
    }

    tree.put("fahbench.major", 2);
    tree.put("fahbench.minor", 1);
    tree.put("fahbench.revis", 1);
    tree.put("openmm.major", 6);
    tree.put("openmm.minor", 2);
    tree.put("openmm.revis", 0);
}


}
}