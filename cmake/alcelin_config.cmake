# alcelin_config.cmake
include(${CMAKE_CURRENT_LIST_DIR}/alcelin_targets.cmake)

install(FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/alcelin_config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/alcelin_config_version.cmake
    DESTINATION ${CMAKE_INSTALL_DATADIR}/alcelin
)
