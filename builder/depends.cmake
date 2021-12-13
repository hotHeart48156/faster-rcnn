#处理依赖
#显示pkgconfig查找，产生${dep}_FOUND变量，如果为正会产生
#使用pkgconfig的包
#如果没找到，就查找当前目录有没有add_${dep}的cmake文件，
#如果当前目录没有找到，就去vcpkg目录查找
set(${PROJECT_NAME}_DEP_HEADS)
set(${PROJECT_NAME}_DEP_LIBRARYS)
set(CMAKE_TOOLCHAIN_FILE  /home/ubuntu/program/vcpkg/scripts/buildsystems/vcpkg.cmake)
find_package(PkgConfig)
set(FOUND_DEPENDS)
set(SUB_PROJECTS_DIR_DEPENDS)
foreach(dep IN ITEMS ${DEPENDS})

    #查找当前builder目录
    file(GLOB_RECURSE FILE_NAME RELATIVE ${CMAKE_CURRENT_LIST_DIR}/ ${CMAKE_CURRENT_LIST_DIR}/*.cmake)
        foreach(file IN ITEMS ${FILE_NAME})
        string(FIND "Find${file}" ${dep} IS_FOUND)
        if(${IS_FOUND}  GREATER  -1)#等于可以用equal，不等要用matches
            set(CURREND_DIR_FOUND_PKG 1)
            break()
        endif()
        endforeach()
    if("${CURREND_DIR_FOUND_PKG}" EQUAL  1)
        include(${CMAKE_CURRENT_LIST_DIR}/Find${dep}.cmake)
        message(STATUS  "FOUND DEPENDS ${dep} IN BUILDER FLODER")

        set(CURREND_DIR_FOUND_PKG 0)
        continue()
    endif()

    #查找子项目
    file(GLOB_RECURSE CMAKES RELATIVE ${PROJECT_SOURCE_DIR}/ ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt)
    message("CMAKES ${CMAKES}")
    set(FOUND)
    foreach(CMAKE IN ITEMS ${CMAKES})
        file(READ ${CMAKE} CMAKE_CONTENT)
        string(FIND ${CMAKE_CONTENT} "project(${dep})"  IS_CONTAINER_DEP)
        if(${IS_CONTAINER_DEP} GREATER -1)
            message(STATUS  "FOUND DEPENDS ${dep} IN SUBPROJECT")
            get_filename_component(SUB_PROJECT_DIR ${CMAKE} DIRECTORY)
            # include_directories(${SUB_PROJECT_DIR}/include)
            list(APPEND SUB_PROJECTS_DIR_DEPENDS  "${SUB_PROJECT_DIR}/include")
            message("SUB_PROJECT_DIR ${SUB_PROJECT_DIR} ${SUB_PROJECTS_DIR_DEPENDS}")
            list(APPEND FOUND_DEPENDS ${dep})
            set(FOUND 1)
            break()
        endif()
    endforeach()
    if("${FOUND}" EQUAL 1)
        set(FOUND 0)
        continue()
    endif()
    

    
    
    pkg_search_module(${dep}  ${dep} QUIET)
    # pkg_check_modules()
    # pkg_get_variable
    if(NOT ${dep}_MODULE_NAME MATCHES "")
        message(STATUS "PKG FOUND ${dep}")
        list(APPEND FOUND_DEPENDS ${dep})
        continue()
    endif()
    
    #查找vcpkg目录，不用条件判断，最后选择
    message(STATUS  "FOUND DEPENDS ${dep} IN VCPKG")
    include(${CMAKE_TOOLCHAIN_FILE})
    find_package(${dep} CONFIG REQUIRED)
    set(VCPKG_DEPEND "${dep}::${dep}")
    list(APPEND FOUND_DEPENDS ${VCPKG_DEPEND})
    continue()
endforeach()
include_directories(${SUB_PROJECTS_DIR_DEPENDS})
target_link_libraries(${PROJECT_NAME}   ${FOUND_DEPENDS})
unset(DEPENDS)









