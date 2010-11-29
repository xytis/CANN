project(CANN)

cmake_minimum_required(VERSION 2.6)

add_subdirectory(src)
include_directories(${CANN_SOURCE_DIR}/include)

set(CANN_SOURCES src/cBrain.cpp src/cNeuron.cpp src/cSensor.cpp main.cpp)

set(BIN_DIR bin/Debug/)

add_executable(${BIN_DIR}CANN ${CANN_SOURCES})
