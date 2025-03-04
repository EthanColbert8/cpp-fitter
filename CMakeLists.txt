cmake_minimum_required(VERSION 3.10)
project(Fitter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER g++)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")
add_executable(fitter.exe ${SOURCES})