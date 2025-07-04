cmake_minimum_required(VERSION 3.20)
project(pokedexapp)

# To maintain: https://github.com/libsdl-org/SDL/blob/main/docs/INTRO-cmake.md

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

add_subdirectory(external/curl EXCLUDE_FROM_ALL)
add_subdirectory(external/SDL EXCLUDE_FROM_ALL)
add_subdirectory(external/SDL_image EXCLUDE_FROM_ALL)
add_subdirectory(external/SDL_ttf EXCLUDE_FROM_ALL)
add_subdirectory(external/json EXCLUDE_FROM_ALL)

add_executable(pokedexapp WIN32
  src/main.cpp
  src/Parser.cpp
  src/Interface.cpp
)

target_link_libraries(pokedexapp PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf libcurl nlohmann_json::nlohmann_json)