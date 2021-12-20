set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/bin)
set(CMAKE_PLUGIN_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/plugins)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-function  -Wunused-variable -Wunused-result -std=c++2a -O3 -fPIC")
set( CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -Wno-unused-function -O3 -fPIC " )
# add_definitions(-D RTTR_DLL)
# add_definitions(-Drefl-cpp_DEVELOPER_MODE=ON)
#开源代码的库路径和头文件路径
set(OSS_PREFIX_LIB_PATH ${OSS_PREFIX_PATH}/lib)
set(OSS_PREFIX_INC_PATH ${OSS_PREFIX_PATH}/include)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/Modules ${CMAKE_MODULE_PATH})
message(STATUS "${PROJECT_NAME} CONTAIN DEPENDS ${DEPENDS}")
if(DEFINED DEPENDS)
    list(LENGTH DEPENDS _DEPENDS_LEN)#list判断长度有时不需要加${}
    #message("DEPENDS_LEN${_DEPENDS_LEN}")#如果一个值可以为空要加冒号
    if( "${_DEPENDS_LEN}" GREATER 0)#判断变量是否定义不需要加$
        include(${CMAKE_CURRENT_LIST_DIR}/depends.cmake)
    endif()
endif()