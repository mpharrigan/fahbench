#include "DefaultHandler.h"

namespace http {
namespace server {

void DefaultHandler::handle_api(vector< string >::const_iterator begin, vector< string >::const_iterator end, boost::property_tree::ptree & tree) {
    tree.put("Unknown", true);
}

}
}