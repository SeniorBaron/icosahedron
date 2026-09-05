cmake_minimum_required(VERSION 3.25)
project(icosahedron)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm   CONFIG REQUIRED)

add_subdirectory(external)
add_subdirectory(src)

