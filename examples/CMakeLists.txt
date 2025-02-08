set(ALCELIN_EXAMPLE_FILES
    "sm/to_string.cpp"
    "sm/formatter.cpp"
    "cu/arithmetics.cpp"
    "cc/boundless_containers.cpp"
    "cc/enumerated_array.cpp"
    "sm/arithmetics.cpp"
    "aec/minesweeper.cpp"
    "file/file_utilized.cpp"
)

function(add_example source executable)
    add_executable(${executable} ${source})
    target_link_libraries(${executable} alcelin)
endfunction()

foreach(example ${ALCELIN_EXAMPLE_FILES})
    set(example_source "${CMAKE_CURRENT_SOURCE_DIR}/${example}")
    string(REPLACE "/" "_" example_executable alcelin_${example})
    string(REPLACE ".cpp" "" example_executable ${example_executable})
    add_example(${example_source} ${example_executable})
endforeach()
