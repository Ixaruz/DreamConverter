file(GLOB BYML_FILES
     "${CMAKE_CURRENT_SOURCE_DIR}/Smmh/S00_*.byml")

foreach(BYML_FILE ${BYML_FILES})
    get_filename_component(BYML_FILE_NAME ${BYML_FILE} NAME)
    configure_file(${BYML_FILE} ${CMAKE_CURRENT_BINARY_DIR}/Smmh/${BYML_FILE_NAME} COPYONLY)
endforeach()
