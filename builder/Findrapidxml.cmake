# list(APPEND FOUND_DEPENDS ${dep})
# add_library(rapidxml INTERFACE)
find_path(RAPIDXML_INCLUDE_DIRS "rapidxml/rapidxml.hpp")
message("RAPIDXML_INCLUDE_DIRS"${RAPIDXML_INCLUDE_DIRS})
# list(APPEND SUB_PROJECTS_DIR_DEPENDS  ${RAPIDXML_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${RAPIDXML_INCLUDE_DIRS})
# message("aaaccc ${RAPIDXML_INCLUDE_DIRS}")
# find_package(rapidxml REQUIRED)
