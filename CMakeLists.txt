cmake_minimum_required(VERSION 2.6)

project(CANN)

Find_Package ( SDL REQUIRED )
Find_Package ( SDL_image REQUIRED )
Find_Package ( SDL_ttf REQUIRED )
Find_Package ( Boost COMPONENTS serialization system filesystem REQUIRED )

set(CANN_SOURCE_DIR "src")

#Special macro for easy including of sources
macro (add_sources)
    file (RELATIVE_PATH _relPath "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
    foreach (_src ${ARGN})
        if (_relPath)
            list (APPEND SRCS "${_relPath}/${_src}")
        else()
            list (APPEND SRCS "${_src}")
        endif()
    endforeach()
    if (_relPath)
        # propagate SRCS to parent directory
        set (SRCS ${SRCS} PARENT_SCOPE)
    endif()
endmacro()

add_subdirectory( ${CANN_SOURCE_DIR} )

include_directories(
    ${CANN_SOURCE_DIR}
    ${Boost_INCLUDE_DIR}
)


if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_FLAGS_Debug "-g")

set(CMAKE_CXX_FLAGS_Release "-O2 -DNDEBUG")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BUILD_TYPE})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x") 

message(STATUS "CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}:${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}}")

link_libraries(
    ${SDL_LIBRARY}
    ${SDLIMAGE_LIBRARY}
    ${SDLTTF_LIBRARY}
)

add_executable(
    CANN
    ${SRCS}
)
