cmake_minimum_required(VERSION 3.1)

project(MiiOS_Kernel)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(. SRC_KERNEL)
add_library(miiosknl SHARED ${SRC_KERNEL})
target_include_directories(miiosknl PUBLIC ../header)
