cmake_minimum_required(VERSION 3.17)

project(fast_particles)



add_subdirectory(src)

if(PROJECT_IS_TOP_LEVEL)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")
    include(DisassemblyView)
    add_subdirectory(test)
endif()