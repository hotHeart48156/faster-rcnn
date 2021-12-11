cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 14)
#添加源文件和头文件
file(GLOB INCLUDE_FILE_h include/*.h)
file(GLOB SRC_FILE_CPP src/*.cpp)
add_executable(${PROJECT_NAME})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
target_sources(
${PROJECT_NAME}
PRIVATE
${INCLUDE_FILE_H}
${SRC_FILE_CPP}
)
include(${CMAKE_CURRENT_LIST_DIR}/common.cmake)
 

set(SUB_PROJECTS)
message("PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")
file(GLOB_RECURSE CHILD_DIRS RELATIVE ${PROJECT_SOURCE_DIR}/ ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt)
#返回所有文件夹的CMakeLists.txt的相对路径
foreach(SUB_DIR IN ITEMS ${CHILD_DIRS})
	if(
	${SUB_DIR} MATCHES "^build"
	OR
	${SUB_DIR} MATCHES "^install"
	)
		message(STATUS  "skip directory ${SUB_DIR}")
	else()
		get_filename_component(SUB_PROJECT ${SUB_DIR} DIRECTORY)
		message(STATUS  "CONTAINER CHILD PROJECT ${SUB_PROJECT}")
		list(APPEND SUB_PROJECTS ${SUB_PROJECT})
endif()
endforeach()
list(LENGTH SUB_PROJECTS SUB_PROJECTS_LEN)
if(${SUB_PROJECTS_LEN} GREATER 0)
    message("add subproject${SUB_PROJECTS}")
	add_subdirectory(${SUB_PROJECTS})
    
endif()







