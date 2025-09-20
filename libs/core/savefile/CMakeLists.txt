set(LIB_SAVEFILE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

set(SOURCES
    "${LIB_SAVEFILE_PATH}/source/savefile.cpp"
    )

set(HEADERS
    "${LIB_SAVEFILE_PATH}/include/savefile/file_hash_details.hpp"
    "${LIB_SAVEFILE_PATH}/include/savefile/file_hash_info.hpp"
    "${LIB_SAVEFILE_PATH}/include/savefile/file_hash_region.hpp"
    "${LIB_SAVEFILE_PATH}/include/savefile/file_hash_revision.hpp"
    "${LIB_SAVEFILE_PATH}/include/savefile/savefile.hpp"
    )

add_library(Core_SaveFile SHARED EXCLUDE_FROM_ALL
    ${SOURCES}
    ${HEADERS}
    )

target_include_directories(Core_SaveFile
    PUBLIC "${LIB_SAVEFILE_PATH}/include"
    )

target_link_libraries(Core_SaveFile
    PUBLIC ACNH
    PRIVATE Core_Util
    )
