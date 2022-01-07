set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/bin)
set(CMAKE_PLUGIN_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/plugins)

# set(CMAKE_CXX_COMPILER_ID "LLVM")
# set(CMAKE_CXX_COMPILER_VERSION 12 CACHE STRING "C++ compiler" FORCE)
# set (CMAKE_CXX_COMPILER  "/usr/bin/clang++-12" CACHE STRING "C++ compiler" FORCE)
# set (CMAKE_C_COMPILER  /usr/bin/clang-12)

# set (CMAKE_AR      "/usr/bin/llvm-ar-12")
# # SET (CMAKE_LINKER  "/usr/bin/llvm-ld-12")
# set (CMAKE_NM      "/usr/bin/llvm-nm-12")
# set (CMAKE_OBJDUMP "/usr/bin/llvm-objdump-12")
# set (CMAKE_RANLIB  "/usr/bin/llvm-ranlib-12")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wmaybe-uninitialized  -Wno-unused-function --std=c++2a -Wunused-variable -Wunused-result -O3 -fPIC")
set( CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -march=native -Wno-unused-function -O3 -fPIC " )
# set(DAW_JSON_NO_CPP_NAMES ON)
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