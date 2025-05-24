add_executable(doubly_linked_list_tests test_list.cpp templates_list.cpp)


target_link_libraries(doubly_linked_list_tests 
	gtest 
)

add_test(doubly_linked_list_tests doubly_linked_list_tests)
