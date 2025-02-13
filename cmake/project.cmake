
macro(gen_executable FOLDER)
    file(GLOB SOURCE_FILES LIST_DIRECTORIES false ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp" "*.c")
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})
    foreach(SOURCE_FILE ${SOURCE_FILES})
        get_filename_component(P_NAME ${SOURCE_FILE} NAME_WE)
        add_executable(${P_NAME} ${SOURCE_FILE})
        set_property(TARGET ${P_NAME} PROPERTY FOLDER ${FOLDER})
    endforeach()    
endmacro(gen_executable)
