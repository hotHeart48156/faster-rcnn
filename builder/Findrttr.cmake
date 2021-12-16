include(${CMAKE_TOOLCHAIN_FILE})
find_package(${dep} CONFIG REQUIRED)
list(APPEND FOUND_DEPENDS RTTR::Core RTTR::Core_Lib)