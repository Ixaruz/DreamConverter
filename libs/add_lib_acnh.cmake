set(LIB_ACNH_PATH "${CMAKE_CURRENT_SOURCE_DIR}/LibACNH")

file(GLOB SOURCES
    "${LIB_ACNH_PATH}/source/*.c*"
    )

file(GLOB HEADERS
    "${LIB_ACNH_PATH}/include/*.h*"
    )

add_library(ACNH SHARED EXCLUDE_FROM_ALL
    ${SOURCES}
    ${HEADERS}
    )

target_include_directories(ACNH
    PUBLIC "${LIB_ACNH_PATH}/include"
    )
