set(src_list
        graph_unitest
        graph_with_data_unitest
        serialization_unitest
        )

foreach (src ${src_list})
    add_executable(${src} ./${src})
    target_link_libraries(${src} ${CMAKE_THREAD_LIBS_INIT} ${GTEST_BOTH_LIBRARIES})
    add_test([GraphTheory]${src} ${src})
endforeach ()
