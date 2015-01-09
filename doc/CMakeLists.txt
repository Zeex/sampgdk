find_package(Doxygen)

if(DOXYGEN_FOUND)
  configure_file(Doxyfile.in Doxyfile @ONLY)

  add_custom_target(sampgdk_doc ALL
                    COMMAND ${DOXYGEN_EXECUTABLE}
                    COMMENT "Building Doxygen documentation"
                    DEPENDS sampgdk
                            ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
  if(CMAKE_GENERATOR MATCHES "Makefile")
    add_custom_target(doc DEPENDS sampgdk_doc)
  endif()

  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html
          DESTINATION share/doc/sampgdk
          COMPONENT doc
          FILES_MATCHING REGEX html/.*)
endif()
