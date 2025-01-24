set(ALCELIN_TESTS
    "${CMAKE_CURRENT_SOURCE_DIR}/test_to_string.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_cu.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_cc.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_sm.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_aec.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_file.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_prop.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/tester.cpp"
)

add_executable(alcelin_tester ${ALCELIN_TESTS})
target_include_directories(alcelin_tester PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(alcelin_tester PRIVATE alcelin)
target_link_libraries(alcelin_tester PRIVATE confer)

add_custom_command(
    TARGET alcelin_tester POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/test_file_read_all_file.txt" "${CMAKE_CURRENT_BINARY_DIR}/test_file_read_all_file.txt"
)
