#!/usr/bin/env bash

ln -s `pwd`/fahbench/ci/travis/boost-configure-gcc-4.9.jam $HOME/user-config.jam

mkdir -p fahbench-build && cd fahbench-build
CC=gcc-4.9  \
CXX=g++-4.9 \
    cmake ../fahbench/                                       \
        -DCMAKE_INSTALL_PREFIX=$HOME/fahbench/               \
        -DINSTALL_ALL_OPENMM_PLUGINS=ON                      \
        -DOPENMM_INCLUDE_PATH=$HOME/openmm/include           \
        -DOPENMM_LIB=$HOME/openmm/lib/libOpenMM.so           \
        -DENABLE_WARNINGS=ON                                 \
        -DMAKE_QT_GUI=ON                                     \

make -j2                      \
    && make install           \
