cmake_minimum_required(VERSION 3.16)
project(faster-rcnn)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/builder)
set(DEPENDS  network  voc_dataset  expat Torch rttr)
include(executable)

