#ifndef VERSION_HANDLER_H
#define VERSION_HANDLER_H





#include "ApiHandler.h"

namespace http {
namespace server {



class VersionHandler : public ApiHandler {

public:
    void handle_api(vector<string>::const_iterator  begin, vector<string>::const_iterator end, pt::ptree & tree);
};

}

}

#endif // VERSION_HANDLER_H
