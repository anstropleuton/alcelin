cmake_minimum_required(VERSION 3.30)

project(alcelin
    VERSION 2.4.0.0
    DESCRIPTION "Alcelin is a collection of utils for Anstro Pleuton's programs."
    LANGUAGES CXX
)

option(ALCELIN_BUILD_TESTS "Build Alcelin tests" OFF)
option(ALCELIN_BUILD_EXAMPLES "Build Alcelin examples" OFF)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/depman.cmake")

depman_declare(confer "https://github.com/anstropleuton/confer.git" origin/main)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(DOXYGEN_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/docs")

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/include/alcelin_config.hpp.in"
    "${CMAKE_CURRENT_BINARY_DIR}/alcelin_config.hpp"
    @ONLY
)
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/pkgconfig.pc.in"
    "${CMAKE_CURRENT_BINARY_DIR}/alcelin.pc"
    @ONLY
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
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/alcelin_config.cmake"
    @ONLY
)

# Taken from GLFW
# Only generate this target if no higher-level project already has
if (NOT TARGET uninstall)
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

set(ALCELIN_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/alcelin.cpp"
)
set(ALCELIN_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/alcelin_ansi_escape_codes.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/alcelin_container_utilities.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/alcelin_custom_containers.hpp"
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

target_compile_options(alcelin PRIVATE
    "$<$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>:-Wall;-Wextra;-Wno-unused;-Wno-shadow>"
    "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/W4>"
)

if(ALCELIN_BUILD_TESTS)
    depman_make_available(confer)
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
