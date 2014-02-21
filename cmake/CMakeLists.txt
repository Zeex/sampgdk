include(CMakePackageConfigHelpers)

set(INCLUDE_INSTALL_DIR include)
set(LIBRARY_INSTALL_DIR lib)

set(config_file sampgdk-config.cmake)
configure_package_config_file(${config_file}.in ${config_file}
                              INSTALL_DESTINATION share/sampgdk/cmake
                              PATH_VARS INCLUDE_INSTALL_DIR
                                        LIBRARY_INSTALL_DIR
                              NO_CHECK_REQUIRED_COMPONENTS_MACRO)

set(version_file sampgdk-version.cmake)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${version_file}
                                 VERSION ${SAMPGDK_VERSION}
                                 COMPATIBILITY SameMajorVersion)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${config_file}
              ${CMAKE_CURRENT_BINARY_DIR}/${version_file}
        DESTINATION share/sampgdk/cmake)

export(PACKAGE sampgdk)
