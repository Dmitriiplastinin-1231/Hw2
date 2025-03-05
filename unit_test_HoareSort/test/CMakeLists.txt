set(SOURCES
    test_hoare.cpp
)

add_executable(test_hoare ${SOURCES})
target_link_libraries(test_hoare
    gtest_main
    gmock_main
    hoare_sort_lib
)

add_test(test_hoare test_hoare)
