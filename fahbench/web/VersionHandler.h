#ifndef VERSION_HANDLER_H
#define VERSION_HANDLER_H


#include <boost/property_tree/ptree.hpp>
#include <vector>
#include <string>

#include "ApiHandler.h"

namespace http {
namespace server {
using std::vector;
using std::string;
namespace pt = boost::property_tree;


class VersionHandler : public ApiHandler {

public:
    void handle_api(vector<string>::const_iterator begin, vector<string>::const_iterator end, pt::ptree & tree);
};

}

}

#endif // VERSION_HANDLER_H
