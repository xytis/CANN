cmake_minimum_required(VERSION 2.6)

project(CANN)

include_directories(${CANN_SOURCE_DIR}/include)

set(
    CANN_SOURCES
    src/cBrain.cpp
    src/cNeuron.cpp
    src/cSensor.cpp
    main.cpp
)

set(
    CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CANN_SOURCE_DIR}/bin/Debug/
)

add_executable(CANN ${CANN_SOURCES})
