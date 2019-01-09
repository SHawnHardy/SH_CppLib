add_executable(graph_unitest ./graph_unitest.cpp)
target_link_libraries(graph_unitest ${GTEST_BOTH_LIBRARIES})
add_test([GraphTheory]graph_unitest graph_unitest)