cmake_minimum_required(VERSION 3.14)

if(DEFINED BUILD_VERSION)
    set(PROJECT_VERSION ${BUILD_VERSION})
else()
    set(PROJECT_VERSION 0.0.0)
endif()

project(DreamConverter
        VERSION ${PROJECT_VERSION}
        )

set(CMAKE_CXX_STANDARD 20)

# include subdirectory
add_subdirectory(libs)

file(GLOB SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.c*"
    )

file(GLOB HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h*"
    )

add_executable(DreamConverter
    ${SOURCES}
    ${HEADERS}
    )

target_include_directories(DreamConverter
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
    )

target_link_libraries(DreamConverter
    PRIVATE ACNH
    )

set(DO_COPY_SMMH CACHE BOOL OFF)

if(DO_COPY_SMMH)
    include(CopySmmh.cmake)
endif(DO_COPY_SMMH)
