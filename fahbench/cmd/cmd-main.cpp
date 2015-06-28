
#include <iostream>
#include <sstream>
#include <functional>
#include <boost/program_options.hpp>
#include <boost/function.hpp>
#include <boost/format.hpp>

#include "../FAHBenchVersion.h"
#include "../Simulation.h"
#include "../WorkUnit.h"
#include "../GPUInfo.h"
#include "../Utils.h"
#include "CommandLineUpdater.h"

namespace po = boost::program_options;
using std::string;
using std::map;

string getGpuDesc() {
    std::stringstream ss;

    try {
        // OpenCL
        auto opencl_devices = GPUInfo::getOpenCLDevices();
        for (auto const & kv : opencl_devices) {
            ss << boost::format("OpenCL Device:\t%1%\tDevice id: %3%\tPlatform id: %2%\tPlatform version: %4%\tDevice version: %5%\t")
               % kv.device() % kv.platform_id() % kv.device_id() % kv.platform_version % kv.device_version << std::endl;
        }
    } catch (const std::exception & err) {
        ss << err.what() << std::endl;
    }

    try {
        // Cuda
        auto cuda_devices = GPUInfo::getCUDADevices();
        for (auto const & kv : cuda_devices) {
            ss << boost::format("CUDA Device:\t%1%\tDevice id: %2%") % kv.device() % kv.device_id() << std::endl;
        }
    } catch (const std::exception & err) {
        ss << err.what() << std::endl;
    }

    return ss.str();
}

int main(int argc, char ** argv) {
    Simulation simulation;
    WorkUnit wu;
    auto setSys = std::bind(&WorkUnit::set_system_fn, &wu, std::placeholders::_1);
    auto setInt = std::bind(&WorkUnit::set_integrator_fn, &wu, std::placeholders::_1);
    auto setState = std::bind(&WorkUnit::set_state_fn, &wu, std::placeholders::_1);
    auto setNSteps = std::bind(&WorkUnit::set_n_steps, &wu, std::placeholders::_1);
    auto setWu = std::bind(&WorkUnit::set_by_name, &wu, std::placeholders::_1);

    po::options_description desc("FAHBench options");
    desc.add_options()
    ("help,h",
     "produce help message")
    ("version,v",
     "version information")
    ("device-info,d",
     "List GPU device information")
    ("list-wus,l",
     "List available work units (WUs)")
    ("device-id",
     po::value<int>()->default_value(0),
     "GPU Device index")
    ("platform-id",
     po::value<int>()->default_value(0),
     "Platform index (OpenCL only)")
    ("platform",
     po::value<string>(&simulation.platform)->default_value("OpenCL"),
     "Platform name (CPU, OpenCL, or CUDA)")
    ("precision",
     po::value<string>(&simulation.precision)->default_value("single"),
     "Precision (single or double)")
    ("workunit,w",
     po::value<string>()->default_value("dhfr")->notifier(setWu),
     "Work unit (WU) name.")
    ("system",
     po::value<string>()->default_value("")->notifier(setSys),
     "Path to system xml file")
    ("state",
     po::value<string>()->default_value("")->notifier(setState),
     "Path to state xml file")
    ("integrator",
     po::value<string>()->default_value("")->notifier(setInt),
     "Path to integrator xml file")
    ("steps",
     po::value<int>()->default_value(9000)->notifier(setNSteps),
     "Number of steps to take")
    ("disable-accuracy-check",
     "Don't check against the reference platform")
    ("enable-accuracy-check",
     "Check against the reference platform (default)")
    ("nan-check",
     po::value<int>(&simulation.nan_check_freq)->default_value(0),
     "Frequency to perform NaN checks during benchmark. 0 - disable.")
    ;

    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    } catch (const po::error & e) {
        std::cerr << "Invalid command line arguments:" << std::endl;
        std::cerr << e.what() << std::endl;
        return 1;
    }

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    if (vm.count("version")) {
        std::cout << "FAHBench version " << getVersion() << std::endl;
        std::cout << "OpenMM version " << getOpenMMVersion() << std::endl;
        return 1;
    }

    if (vm.count("device-info")) {
        std::cout << "Available devices" << std::endl;
        std::cout << "-----------------" << std::endl << std::endl;
        std::cout << getGpuDesc() << std::endl;
        return 1;
    }

    if (vm.count("list-wus")) {
        for (auto & wuname : wu.available_wus()) {
            std::cout << "WU: " << wuname << std::endl;
        }
        return 1;
    }

    if (vm.count("disable-accuracy-check")) {
        simulation.verifyAccuracy = false;
    }

    if (vm.count("enable_accuracy-check")) {
        simulation.verifyAccuracy = true;
    }

    std::cout << simulation.summary() << std::endl;

    CommandLineUpdater updater;
    double score = simulation.run(updater);
    updater.message(boost::format("Final score: %1$.4f") % score);
}
