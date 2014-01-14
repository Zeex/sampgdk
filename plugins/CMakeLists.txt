file(RELATIVE_PATH folder ${PROJECT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(helloworld)
set_property(TARGET helloworld PROPERTY FOLDER ${folder})
