# @file CMakeLists.txt
# @author Fande Yu 
# @version 0.1 
# @copyright 
#
# ChangeLog
# AUTHOR      | TIME       | VERSION       | DESCRIPTION
# ------      | ----       | -------       | -----------
# Fande Yu    | 2020/10/14 | 0.1.20201014  | Create this file 
# Fande Yu        | 2020/12/26 | 0.1.20201226  | Build Seperatedly

#Notice
#1. export CC=gcc and CXX=g++ ahead of running this CMake file.
#2. If this program will be run on multi-nodes where NCCL may be necessary, this file need to be modified.

# CMAKE REQUIREMENT
#export CC=/opt/intel/oneapi/compiler/2021.2.0/linux/bin/intel64/icc
#export CXX=/opt/intel/oneapi/compiler/2021.2.0/linux/bin/intel64/icpc

SET(CMAKE_C_COMPILER /opt/intel/oneapi/compiler/2021.2.0/linux/bin/intel64/icc)
SET(CMAKE_CXX_COMPILER /opt/intel/oneapi/compiler/2021.2.0/linux/bin/intel64/icpc)

cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(TomoProject)

set(TomoProject_VERSION_MAJOR 0)
set(TomoProject_VERSION_MINOR 1)
set(TomoProject_VERSION_ADDIT 20201014)

#Get git commit
execute_process(
    COMMAND git rev-parse HEAD
    OUTPUT_VARIABLE COMMIT_VERSION
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
message(STATUS "Welcome to TomoProject ${TomoProject_VERSION_MAJOR}.${TomoProject_VERSION_MINOR}.${TomoProject_VERSION_ADDIT}!")


#For TomoConfig.h.in
set(COMMIT_VERSION_QUOTE "\"${COMMIT_VERSION}\"")

#set(CMAKE_C_COMPILER icc)
#set(CMAKE_CXX_COMPILER icpc)
set(COMMON_FLAGS "-std=gnu99 ${COMMON_FLAGS}")

#For FFTW
option(SINGLE_PRECISION "Whether to use single float precision in calculation?" ON)

#Only option is useful for #cmakedefine in TomoConfig.h.in
option(CPU_VERSION "Whether to use CPU to calculate?" ON)


#Add compilation flag part1: build type
if("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE "release")
endif("${CMAKE_BUILD_TYPE}" STREQUAL "")
if("${CMAKE_BUILD_TYPE}" STREQUAL "release")
    set(COMMON_FLAGS "${COMMON_FLAGS} -fopenmp -O2")
    message(STATUS "CMAKE_BUILD_TYPE : ${CMAKE_BUILD_TYPE}, compile ${CMAKE_PROJECT_NAME} with ${COMMON_FLAGS} flag.")
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "debug")
    #TODO 拆成additional_flags
    set(COMMON_FLAGS "${COMMON_FLAGS} -fopenmp -O2")
    set(COMMON_FLAGS "${COMMON_FLAGS} -g")
    message(STATUS "CMAKE_BUILD_TYPE : ${CMAKE_BUILD_TYPE}, compile ${CMAKE_PROJECT_NAME} with ${COMMON_FLAGS} flag.")
endif("${CMAKE_BUILD_TYPE}" STREQUAL "release")

if("${CPU_VERSION}")
    message(STATUS "Try to build Tomo-Project in CPU version.")
endif("${CPU_VERSION}")


#Add compilation flags part2: library flags
#set(COMMON_FLAGS "${COMMON_FLAGS} -lutil -lcore -lz -lpthread -lm -lfftw3f -lfftw3f_threads")
#这里要特别注意 由于FFTW是从源文件进行编译，打包成库，在target_link_libraries中用${FFTW_LIBRARIES}变量进行指定，所以在这里指定编译器flags时，不能加入-lfftw3f等等。
#-lcore -lutil同理
set(COMMON_FLAGS "${COMMON_FLAGS} -lz -lpthread -lm ")

set(CMAKE_C_FLAGS "${COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS}")

#output flags
message(STATUS "CMAKE_C_FLAGS : ${CMAKE_C_FLAGS}")
message(STATUS "CMAKE_CXX_FLAGS : ${CMAKE_CXX_FLAGS}")

#用于载入已有的CMakeLists文件
#载入FFTW的CMakeLists文件
include(${CMAKE_SOURCE_DIR}/cmake/BuildFFTW.cmake)
message(STATUS "FFTW Path: ${FFTW_PATH}")
# 将fftw安装之后的头文件目录加入
include_directories(${FFTW_PATH}/include)

include_directories(${CMAKE_SOURCE_DIR}/external/Eigen)
include_directories(${CMAKE_SOURCE_DIR}/src/include)



#Config

if("${CPU_VERSION}")


        file(GLOB_RECURSE CORE_SOURCES ${CMAKE_SOURCE_DIR}/src/core/*.cpp)
        add_library(core_CPU STATIC ${CORE_SOURCES})
        add_dependencies(core_CPU FFTW)
        target_link_libraries(core_CPU PUBLIC ${FFTW_LIBRARIES})

        file(GLOB_RECURSE UTIL_SOURCES ${CMAKE_SOURCE_DIR}/src/util/*.cpp)
        add_library(util STATIC ${UTIL_SOURCES})

        file(GLOB_RECURSE MAIN_SOURCES ${CMAKE_SOURCE_DIR}/src/main/*.cpp)

        foreach(MAINSRC ${MAIN_SOURCES})
            get_filename_component(MAINNAME ${MAINSRC} NAME_WE) # file name without directories or longest extension
                set(MAINNAME "${MAINNAME}_cpu")
            add_executable(${MAINNAME} ${MAINSRC})
            target_link_libraries(${MAINNAME} PUBLIC core_CPU util  ${FFTW_LIBRARIES})
        endforeach()

endif("${CPU_VERSION}")
