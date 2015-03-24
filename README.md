FAHBench
========

FAHBench is the official Folding@Home benchmark desigend to work on any
OpenCL compatible device. A CUDA platform is also available for machines
with NVIDIA GPUs. License under GPLv2.

Requirements
------------

 - [CMake](http://www.cmake.org/)  
 - [Boost](http://www.boost.org/)
 - [Qt5](http://qt-project.org/)  
 - [OpenMM](http://openmm.org/)

Building
--------

### Linux

TODO

### Windows

 1. Download and install 
	  - Visual Studio - VS Community 2013 works well.
	  - Qt5
	  - Cmake
	  - CUDA SDK

	These all have nice GUI installers.

 2. Download Boost. You actually have to extract the archive,
    and build it from the command line. The
    "ProgramOptions" module is *not* header-only.
	```
	bootstrap
	.\b2 address-model=64 # need 64 bit!
	```

 3. Download OpenMM and build OpenMM with CMake. I don't think the provided binaries (VC2010)
    will work. Build the release configuration. You can disable building the python bindings
	(which may be a source of build errors). "Build" the `INSTALL` "project" to install OpenMM.

 4. Run CMake on the fahbench source directory. Finagle it until it has found
    all of the dependencies you just spent so long getting in order. I had to set
	 - `CMAKE_PREFIX_PATH` to `.../Qt/5.4/msvc2013_64/`
	 - `BOOST_ROOT` to where I compiled	Boost. 
	 - `BOOST_LIBRARY_DIR` to `...boost/stage/lib/`

 5. Build and install! CMake will copy the relevant OpenMM and Qt `dll`s to the `bin/`
    install directory.

