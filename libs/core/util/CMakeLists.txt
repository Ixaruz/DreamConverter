set(LIB_UTIL_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

set(SOURCES
    "${LIB_UTIL_PATH}/source/util.cpp"
    )

set(HEADERS
    "${LIB_UTIL_PATH}/include/util/util.hpp"
    )

add_library(Core_Util SHARED EXCLUDE_FROM_ALL
    ${SOURCES}
    ${HEADERS}
    )

target_include_directories(Core_Util
    PUBLIC "${LIB_UTIL_PATH}/include"
    )

target_link_libraries(Core_Util
    PUBLIC ACNH
    )
