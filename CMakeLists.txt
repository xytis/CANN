cmake_minimum_required(VERSION 2.6)

project(CANN)

Find_Package ( SDL REQUIRED )
Find_Package ( SDL_image REQUIRED )
Find_Package ( SDL_ttf REQUIRED )

include_directories(
    ${CANN_SOURCE_DIR}/include
)

set(
    CANN_SOURCES
    src/cBrain.cpp
    src/cMainControler.cpp
    src/cMenuState.cpp
    src/cMover.cpp
    src/cNeuron.cpp
    src/cRenderState.cpp
    src/cResourceManager.cpp
    src/cSensor.cpp
    src/sdl_video.cpp
    main.cpp
)

set(
    CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CANN_SOURCE_DIR}/bin/Debug/
)

link_libraries (
    ${SDL_LIBRARY}
    ${SDLIMAGE_LIBRARY}
    ${SDLTTF_LIBRARY}
)

add_executable(
    CANN
    ${CANN_SOURCES}
)
