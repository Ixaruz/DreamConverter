set(LIB_SAVE_STRUCTS_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

set(SOURCES
    "${LIB_SAVE_STRUCTS_PATH}/source/save_struct.cpp"
    "${LIB_SAVE_STRUCTS_PATH}/source/save_land_my_design.cpp"
    "${LIB_SAVE_STRUCTS_PATH}/source/save_land_time.cpp"
    "${LIB_SAVE_STRUCTS_PATH}/source/save_main_field.cpp"
    "${LIB_SAVE_STRUCTS_PATH}/source/save_npc_house_list.cpp"
    "${LIB_SAVE_STRUCTS_PATH}/source/save_npc.cpp"
    "${LIB_SAVE_STRUCTS_PATH}/source/save_player_house_list.cpp"
    "${LIB_SAVE_STRUCTS_PATH}/source/save_shop.cpp"
    )

set(HEADERS
    "${LIB_SAVE_STRUCTS_PATH}/include/save_structs/save_struct.hpp"
    "${LIB_SAVE_STRUCTS_PATH}/include/save_structs/save_struct.inl"
    "${LIB_SAVE_STRUCTS_PATH}/include/save_structs/save_land_my_design.hpp"
    "${LIB_SAVE_STRUCTS_PATH}/include/save_structs/save_land_time.hpp"
    "${LIB_SAVE_STRUCTS_PATH}/include/save_structs/save_main_field.hpp"
    "${LIB_SAVE_STRUCTS_PATH}/include/save_structs/save_npc_house_list.hpp"
    "${LIB_SAVE_STRUCTS_PATH}/include/save_structs/save_npc.hpp"
    "${LIB_SAVE_STRUCTS_PATH}/include/save_structs/save_player_house_list.hpp"
    "${LIB_SAVE_STRUCTS_PATH}/include/save_structs/save_shop.hpp"
    )

add_library(Core_SaveStructs SHARED EXCLUDE_FROM_ALL
    ${SOURCES}
    ${HEADERS}
    )

target_include_directories(Core_SaveStructs
    PUBLIC "${LIB_SAVE_STRUCTS_PATH}/include"
    )

target_link_libraries(Core_SaveStructs
    PUBLIC ACNH
    )
