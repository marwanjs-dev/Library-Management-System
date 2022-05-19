cmake_minimum_required(VERSION 3.3)
project(assignment1)

set(CMAKE_CXX_STANDARD 17)
file(GLOB SOURCES
        /home/marwan/Documents/jsoncpp-master/include/json/*.h
        /home/marwan/Documents/jsoncpp-master/dist/json/*.h
        /home/marwan/Documents/jsoncpp-master/dist/*.cpp
        )
add_executable(yourProj ${SOURCES})
add_executable(assignment1 main.cpp entities.h)

include(FindPkgConfig)
PKG_SEARCH_MODULE(Jsoncpp REQUIRED jsoncpp)
include_directories(${Jsoncpp_INCLUDE_DIR})
target_link_libraries(assignment1 ${Jsoncpp_LIBRARY})