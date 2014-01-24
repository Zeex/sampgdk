find_package(Doxygen)

if(DOXYGEN_FOUND)
  configure_file(Doxyfile.in Doxyfile @ONLY)
  add_custom_target(sampgdk_doxygen ALL
                    COMMAND ${DOXYGEN_EXECUTABLE}
                    COMMENT "Building Doxygen documentation") 
endif()

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DESTINATION .
        COMPONENT doc
        PATTERN .git* EXCLUDE
        PATTERN CMakeLists.txt EXCLUDE)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	    DESTINATION .
	    COMPONENT doc
        FILES_MATCHING REGEX html/.*)
