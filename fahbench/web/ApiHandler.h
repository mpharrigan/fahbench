#ifndef APIHANDLER_H
#define APIHANDLER_H

#include <boost/property_tree/ptree.hpp>
#include <vector>
#include <string>

namespace http {
namespace server {
using std::vector;
using std::string;
namespace pt = boost::property_tree;

class ApiHandler {
public:
    virtual void handle_api(vector<string>::const_iterator begin, vector<string>::const_iterator end, pt::ptree & tree) = 0;
    virtual ~ApiHandler() = default;
};

}
}
#endif // APIHANDLER_H
