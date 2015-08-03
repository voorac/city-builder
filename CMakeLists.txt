project(CityBuilder CXX)

cmake_minimum_required(VERSION 3.0.2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CXX_COMPILER_FLAGS "${CXX_COMPILER_FLAGS} -std=c++14")

find_package(SFML COMPONENTS system window REQUIRED)

include_directories(${SFML_INCLUDE_DIR})

add_executable(hello hello.cpp)

target_link_libraries(hello ${SFML_SYSTEM_LIBRARY_RELEASE} ${SFML_WINDOW_LIBRARY_RELEASE})


