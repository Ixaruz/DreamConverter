cmake_minimum_required(VERSION 3.22)

if(DEFINED BUILD_VERSION)
    set(PROJECT_VERSION ${BUILD_VERSION})
else()
    set(PROJECT_VERSION 0.0.0)
endif()

project(DreamConverter
        VERSION ${PROJECT_VERSION}
        )

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# include subdirectory
add_subdirectory(libs)
add_subdirectory(tools)

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
    PRIVATE Core
    PRIVATE ACNH
    )


# If anyone is ever reading this; for updating generated_offsets.hpp:
# 1. Get the Smmh files from the RomFs of Animal Crossing: New Horizons (preferably the latest update as this tool is designed around that)
# 2. Place them in a "Smmh" folder in this directory
# 3. Enable the option below and build the project once
# 4. Disable the option again to avoid regenerating the file every build
option(DREAM_CONVERTER_GENERATE_OFFSETS "Generate offsets for Smmh files" OFF)

add_custom_target(generated_offsets DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/generated_offsets.hpp)
add_dependencies(DreamConverter generated_offsets)

if (DREAM_CONVERTER_GENERATE_OFFSETS)
    message(STATUS "Smmh offset generation is enabled; will generate generated_offsets.hpp")

    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/include/generated_offsets.hpp
        COMMAND save_offset_extractor "${CMAKE_CURRENT_SOURCE_DIR}/include/generated_offsets.hpp"
        DEPENDS save_offset_extractor
            # "${CMAKE_CURRENT_SOURCE_DIR}Smmh/S00_111_103.byml"
            # "${CMAKE_CURRENT_SOURCE_DIR}/Smmh/S00_120_109.byml"
            # "${CMAKE_CURRENT_SOURCE_DIR}/Smmh/S00_131080_131078.byml"
            # "${CMAKE_CURRENT_SOURCE_DIR}/Smmh/S00_262152_262146.byml"
            "${CMAKE_CURRENT_SOURCE_DIR}/Smmh/S00_327691_327681.byml"
            "${CMAKE_CURRENT_SOURCE_DIR}/Smmh/S00_393228_393217.byml"
            "${CMAKE_CURRENT_SOURCE_DIR}/Smmh/S00_458758_458753.byml"
            "${CMAKE_CURRENT_SOURCE_DIR}/Smmh/S00_475141_475137.byml"
            "${CMAKE_CURRENT_SOURCE_DIR}/Smmh/S00_491521_491521.byml"
            "${CMAKE_CURRENT_SOURCE_DIR}/Smmh/S00_507910_507905.byml"
            "${CMAKE_CURRENT_SOURCE_DIR}/Smmh/S00_512004_512001.byml"
            "${CMAKE_CURRENT_SOURCE_DIR}/Smmh/S00_516097_516097.byml"
            "${CMAKE_CURRENT_SOURCE_DIR}/Smmh/S00_524421_524297.byml"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating Smmh offsets"
    )
endif(DREAM_CONVERTER_GENERATE_OFFSETS)

include(CPackInstaller.cmake)
