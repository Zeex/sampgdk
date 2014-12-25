if(SAMPGDK_BUILD_DOCS)
  find_package(Doxygen)
endif()

if(DOXYGEN_FOUND)
  configure_file(Doxyfile.in Doxyfile @ONLY)
  add_custom_target(sampgdk_doc ALL
                    COMMAND ${DOXYGEN_EXECUTABLE}
                    COMMENT "Building Doxygen documentation"
                    DEPENDS sampgdk)
  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html
          DESTINATION share/doc/sampgdk
          COMPONENT doc
          FILES_MATCHING REGEX html/.*)
endif()
