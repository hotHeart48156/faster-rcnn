cmake_minimum_required(VERSION 3.16)
file(GLOB INCLUDE_FILE_h include/*.h)
file(GLOB SRC_FILE_CPP src/*.cpp)
add_library(${PROJECT_NAME} SHARED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
target_sources(
${PROJECT_NAME}
PRIVATE
${INCLUDE_FILE_H}
${SRC_FILE_CPP}
)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
include(${CMAKE_CURRENT_LIST_DIR}/common.cmake)


    
