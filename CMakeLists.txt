cmake_minimum_required(VERSION 3.19)
project(graphicsApp3)

set(CMAKE_CXX_STANDARD 14)
set(CONAN_CMAKE_CXX_STANDARD 14)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(graphicsApp3 main.cpp Canvas.cpp Canvas.h cell.cpp cell.h)

target_link_libraries(graphicsApp3 ${CONAN_LIBS})