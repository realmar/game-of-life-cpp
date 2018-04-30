cmake_minimum_required (VERSION 3.1.0)
project (game-of-life)

find_package(OpenGL REQUIRED)

add_executable(game-of-life main.cpp)
target_link_libraries(game-of-life ${OPENGL_LIBRARIES})