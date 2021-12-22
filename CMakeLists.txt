cmake_minimum_required(VERSION 3.16)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_COMPILER_VERSION 12 CACHE STRING "C++ compiler" FORCE)
set(CMAKE_CXX_COMPILER_ID "LLVM")
set (CMAKE_C_COMPILER  /usr/bin/clang-12)
set (CMAKE_CXX_COMPILER  "/usr/bin/clang++-12" CACHE STRING "C++ compiler" FORCE)
project(faster-rcnn)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/builder)
set(DEPENDS Python Torch  network    expat  voc_dataset)
include(executable)

