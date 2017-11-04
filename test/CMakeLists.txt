macro(add_unit_test target source libs includes)
    add_executable(${target}
        ${source})

    target_link_libraries(${target} 
        ${libs})

    target_include_directories(${target} SYSTEM PUBLIC
        ${includes})

    add_test(NAME ${target}
             COMMAND ${target}
             WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endmacro()

add_unit_test(arrays arrays.cpp "" "")
add_unit_test(bst bst.cpp "" "")
add_unit_test(hash hash.cpp "" "")
add_unit_test(heaps heaps.cpp "" "")
add_unit_test(primitives primitives.cpp "" "")
add_unit_test(lists lists.cpp "" "")
add_unit_test(strings strings.cpp "" "")
add_unit_test(stacks stacks.cpp "" "")
add_unit_test(search search.cpp "" "")
add_unit_test(sorting sorting.cpp "" "")
add_unit_test(trees trees.cpp "" "")
