project(CityBuilder CXX)

cmake_minimum_required(VERSION 3.0.2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++14")

find_package(SFML COMPONENTS system window graphics REQUIRED)

include_directories(${SFML_INCLUDE_DIR})

add_executable(cityb
  main.cpp
  game.cpp
  game_state_start.cpp
  game_state_editor.cpp
  animation_handler.cpp
  texture_manager.cpp
  tile.cpp
  gui.cpp
  map.cpp
  city.cpp)

target_link_libraries(cityb ${SFML_SYSTEM_LIBRARY_DEBUG} ${SFML_WINDOW_LIBRARY_DEBUG} ${SFML_GRAPHICS_LIBRARY_DEBUG})

configure_file("media/background.png" "${CMAKE_CURRENT_BINARY_DIR}/media/background.png" COPYONLY)
configure_file("media/commercial.png" "${CMAKE_CURRENT_BINARY_DIR}/media/commercial.png" COPYONLY)
configure_file("media/font.ttf" "${CMAKE_CURRENT_BINARY_DIR}/media/font.ttf" COPYONLY)
configure_file("media/forest.png" "${CMAKE_CURRENT_BINARY_DIR}/media/forest.png" COPYONLY)
configure_file("media/grass.png" "${CMAKE_CURRENT_BINARY_DIR}/media/grass.png" COPYONLY)
configure_file("media/industrial.png" "${CMAKE_CURRENT_BINARY_DIR}/media/industrial.png" COPYONLY)
configure_file("media/residential.png" "${CMAKE_CURRENT_BINARY_DIR}/media/residential.png" COPYONLY)
configure_file("media/road.png" "${CMAKE_CURRENT_BINARY_DIR}/media/road.png" COPYONLY)
configure_file("media/water.png" "${CMAKE_CURRENT_BINARY_DIR}/media/water.png" COPYONLY)
configure_file("media/city_cfg.dat" "${CMAKE_CURRENT_BINARY_DIR}/media/city_cfg.dat" COPYONLY)
configure_file("media/city_map.dat" "${CMAKE_CURRENT_BINARY_DIR}/media/city_map.dat" COPYONLY)



