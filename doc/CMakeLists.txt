find_package(Doxygen)

if(DOXYGEN_FOUND)
  configure_file(Doxyfile.in Doxyfile @ONLY)

  add_custom_target(sampgdk_doc ALL
                    COMMAND ${DOXYGEN_EXECUTABLE}
                    COMMENT "Building Doxygen documentation")
  add_dependencies(sampgdk_doc sampgdk)

  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html
          DESTINATION share/doc/sampgdk
          COMPONENT doc
          FILES_MATCHING REGEX html/.*)
endif()

