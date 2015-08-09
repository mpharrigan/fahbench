#include "DeviceHandler.h"

#include "../GPUInfo.h"
#include "../Device.h"

namespace http {
namespace server {

void DeviceHandler::handle_api(vector< string >::const_iterator begin, vector< string >::const_iterator end, boost::property_tree::ptree & tree) {

    pt::ptree devices;
    try {
        // OpenCL
        auto opencl_devices = GPUInfo::getOpenCLDevices();
        for (auto const & kv : opencl_devices) {
            pt::ptree device;
            device.put("name", kv.device());
            device.put("device_id", kv.device_id());
            device.put("platform_id", kv.platform_id());
            device.put("platform_version", kv.platform_version);
            device.put("device_version", kv.device_version);
            device.put("platform", "OpenCL");
            devices.push_back(std::make_pair("", device));
        }
    } catch (const std::exception & err) {
        tree.add("errors.what", err.what());
    }


    try {
        // Cuda
        auto cuda_devices = GPUInfo::getCUDADevices();
        for (auto const & kv : cuda_devices) {
            pt::ptree device;
            device.put("name", kv.device());
            device.put("device_id", kv.device_id());
            device.put("platform", "CUDA");
            devices.push_back(std::make_pair("", device));
        }
    } catch (const std::exception & err) {
        tree.add("errors.what", err.what());
    }

    tree.add_child("devices", devices);


}


}
}