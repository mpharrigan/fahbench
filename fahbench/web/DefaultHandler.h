#ifndef DEFAULTHANDLER_H
#define DEFAULTHANDLER_H

#include <boost/property_tree/ptree.hpp>
#include <vector>
#include <string>

#include "ApiHandler.h"

namespace http {
namespace server {
using std::vector;
using std::string;
namespace pt = boost::property_tree;

class DefaultHandler : public ApiHandler {
public:
    void handle_api(vector<string>::const_iterator  begin, vector<string>::const_iterator end, pt::ptree & tree);
};

}
}

#endif // DEFAULTHANDLER_H
