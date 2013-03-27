file(RELATIVE_PATH folder ${PROJECT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory("helloworld")
set_property(TARGET helloworld PROPERTY FOLDER "${folder}")

add_subdirectory("lvdm")
set_property(TARGET lvdm PROPERTY FOLDER "${folder}")

add_subdirectory("unlimitedfs")
set_property(TARGET unlimitedfs PROPERTY FOLDER "${folder}")