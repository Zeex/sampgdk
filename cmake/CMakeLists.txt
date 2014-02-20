include(CMakePackageConfigHelpers)

string(TOUPPER "${PROJECT_NAME}" PROJECT_NAME_UC)
string(TOLOWER "${PROJECT_NAME}" PROJECT_NAME_LC)

set(INCLUDE_INSTALL_DIR include)
set(LIBRARY_INSTALL_DIR lib)

set(config_file ${PROJECT_NAME_UC}Config.cmake)
configure_package_config_file(${config_file}.in ${config_file}
                              INSTALL_DESTINATION share/${PROJECT_NAME_LC}/cmake
                              PATH_VARS INCLUDE_INSTALL_DIR
                                        LIBRARY_INSTALL_DIR
                              NO_CHECK_REQUIRED_COMPONENTS_MACRO)

set(version_file SAMPGDKVersion.cmake)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${version_file}
                                 VERSION ${SAMPGDK_VERSION}
                                 COMPATIBILITY SameMajorVersion)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${config_file}
              ${CMAKE_CURRENT_BINARY_DIR}/${version_file}
        DESTINATION share/${PROJECT_NAME_LC}/cmake)

export(PACKAGE ${PROJECT_NAME_UC})
