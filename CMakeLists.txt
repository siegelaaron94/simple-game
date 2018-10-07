cmake_minimum_required(VERSION 3.10)
project(simple-game)

configure_file(settings.json ${CMAKE_BINARY_DIR}/data/settings.json)

add_executable(simple-game
    src/main.cpp
    src/simple_game.cpp
)

target_include_directories(simple-game PUBLIC include)
target_link_libraries(simple-game PUBLIC sigma-core sigma-opengl SDL2::SDL2 Assimp::assimp)

target_package_resources(simple-game resources)

add_dependencies(simple-game sigma-opengl-resources simple-game-resources)

if(COTIRE_CMAKE_MODULE_VERSION)
  cotire(simple-game)
endif()
