
# order matters as some libraries depend on others
add_subdirectory(util)
add_subdirectory(savefile)
add_subdirectory(save_structs)

add_library(Core INTERFACE EXCLUDE_FROM_ALL)

target_link_libraries(Core
    INTERFACE Core_Util
    INTERFACE Core_SaveFile
    INTERFACE Core_SaveStructs
    )
