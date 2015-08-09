#ifndef DEVICEHANDLER_H
#define DEVICEHANDLER_H

#include "ApiHandler.h"

namespace http {
namespace server {

class DeviceHandler : public ApiHandler {
public:
    void handle_api(vector<string>::const_iterator begin, vector<string>::const_iterator end, pt::ptree & tree);
};

}
}

#endif // DEVICEHANDLER_H
