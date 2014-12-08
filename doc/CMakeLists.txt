find_package(Doxygen)

configure_file(Doxyfile.in Doxyfile @ONLY)

if(DOXYGEN_FOUND)
  add_custom_target(sampgdk_doc ALL
                    COMMAND ${DOXYGEN_EXECUTABLE}
                    COMMENT "Building Doxygen documentation")
  add_dependencies(sampgdk_doc sampgdk)
endif()

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html
        DESTINATION share/doc/sampgdk
        COMPONENT doc
        FILES_MATCHING REGEX html/.*)
