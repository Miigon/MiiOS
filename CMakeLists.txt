cmake_minimum_required(VERSION 3.1)

add_subdirectory(kernel)
add_subdirectory(drivers)

project(MiiOS)

set(CMAKE_CXX_STANDARD 14)

add_executable(boot main.cpp)
target_include_directories(boot PUBLIC header)
target_link_libraries(boot miiosknl)
add_dependencies(boot miiosknl)
