project(CityBuilder CXX)

cmake_minimum_required(VERSION 3.0.2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++14")

find_package(SFML COMPONENTS system window graphics REQUIRED)

include_directories(${SFML_INCLUDE_DIR})

add_executable(cityb main.cpp game.cpp game_state_start.cpp game_state_editor.cpp)

target_link_libraries(cityb ${SFML_SYSTEM_LIBRARY_DEBUG} ${SFML_WINDOW_LIBRARY_DEBUG} ${SFML_GRAPHICS_LIBRARY_DEBUG})



