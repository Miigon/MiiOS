cmake_minimum_required(VERSION 3.1)

project(MiiOS_Driver)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_SHARED_LIBRARY_SUFFIX .drv)
set(CMAKE_SHARED_LIBRARY_PREFIX )

link_libraries(miiosknl)
include_directories(../header)

aux_source_directory(realdisk REALDISK_SRC)
add_library(realdisk SHARED ${REALDISK_SRC})
