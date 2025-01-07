cmake_minimum_required(VERSION 3.30)

project(alcelin
    VERSION 2.0.0.0
    DESCRIPTION "Alcelin is a collection of utils for Anstro Pleuton's programs."
    HOMEPAGE_URL "https://anstropleuton.github.io/alcelin/"
    LANGUAGES CXX
)

option(ALCELIN_BUILD_TESTS "Build Alcelin tests" OFF)
option(ALCELIN_BUILD_EXAMPLES "Build Alcelin examples" OFF)

if(NOT DEFINED ALCELIN_CONFER_PATH)
    set(ALCELIN_CONFER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/deps/confer")
endif()
option(ALCELIN_FORCE_USE_CONFER_PATH "Force use Confer from subdirectory" OFF)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(DOXYGEN_ALCELIN_PROJECT_VERSION ${PROJECT_VERSION})
set(DOXYGEN_ALCELIN_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/docs")

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/include/alcelin_config.hpp.in"
    "${CMAKE_CURRENT_BINARY_DIR}/alcelin_config.hpp"
)
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/alcelin.pc.in"
    "${CMAKE_CURRENT_BINARY_DIR}/alcelin.pc"
)
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in"
    "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
    @ONLY
)
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/docs/header.html.in"
    "${CMAKE_CURRENT_BINARY_DIR}/header.html"
    @ONLY
)
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/docs/footer.html.in"
    "${CMAKE_CURRENT_BINARY_DIR}/footer.html"
    @ONLY
)

set(ALCELIN_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/alcelin.cpp"
)
set(ALCELIN_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/alcelin_ansi_escape_codes.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/alcelin_container_utilities.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/alcelin_file_utilities.hpp"
    "${CMAKE_CURRENT_BINARY_DIR}/alcelin_config.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/alcelin.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/alcelin_string_manipulators.hpp"
)
set(ALCELIN_INCLUDE_DIRS
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_BINARY_DIR}"
)

add_library(alcelin)
target_compile_features(alcelin PUBLIC cxx_std_23)
target_sources(alcelin PRIVATE ${ALCELIN_SOURCES})
target_sources(alcelin PUBLIC
    FILE_SET HEADERS
    BASE_DIRS ${ALCELIN_INCLUDE_DIRS}
    FILES ${ALCELIN_HEADERS}
)

if(ALCELIN_BUILD_TESTS)
    find_package(confer QUIET)
    if(NOT confer_FOUND)
        message("---> confer not found in system, adding subdirectory ${ALCELIN_CONFER_PATH}")
        add_subdirectory(${ALCELIN_CONFER_PATH})
    elseif(ALCELIN_FORCE_USE_CONFER_PATH)
        message("---> Force using subdirectory ${ALCELIN_CONFER_PATH} for confer")
        add_subdirectory(${ALCELIN_CONFER_PATH})
    else()
        message("---> confer found in system, using it instead")
    endif()
    add_subdirectory(tests)
endif()

if(ALCELIN_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/alcelin_config_version.cmake"
    COMPATIBILITY AnyNewerVersion
)

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/alcelin_config_version.cmake"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/alcelin"
)
install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/alcelin.pc"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
)
install(
    TARGETS alcelin
    EXPORT alcelin_targets
    FILE_SET HEADERS
)
install(
    EXPORT alcelin_targets
    NAMESPACE alcelin::
    DESTINATION "${CMAKE_INSTALL_DATADIR}/alcelin"
)

# Taken from GLFW
# Only generate this target if no higher-level project already has
if(NOT TARGET uninstall)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY
    )

    add_custom_target(uninstall
        "${CMAKE_COMMAND}" -P
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    )
endif()
