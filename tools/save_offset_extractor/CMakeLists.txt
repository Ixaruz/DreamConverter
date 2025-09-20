
add_executable(save_offset_extractor EXCLUDE_FROM_ALL
    "save_offset_extractor.cpp"
    "smmh_paths_by_revision.cpp"
    )

target_link_libraries(save_offset_extractor
    PRIVATE Core_SaveFile
    PRIVATE Core_Util
    PRIVATE ACNH
    )
