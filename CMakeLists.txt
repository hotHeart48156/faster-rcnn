cmake_minimum_required(VERSION 3.16)
project(faster-rcnn)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/builder)
set(DEPENDS Python Torch  network    expat  voc_dataset)
include(executable)

