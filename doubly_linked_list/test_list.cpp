#include <gtest/gtest.h>

#include "doubly_linked_list.hpp"

using biv::DoublyLinkedList;

TEST(doubly_linked_list, PushBackAndSize) {
    DoublyLinkedList<std::string> v;
    v.push_back("first");
    v.push_back("second");

    EXPECT_EQ(v.get_size(), 2);
    EXPECT_TRUE(v.has_item("first"));
    EXPECT_TRUE(v.has_item("second"));
}

TEST(doubly_linked_list, HasItemWithDifferentTypes) {
    DoublyLinkedList<double> v;
    v.push_back(3.14);
    v.push_back(2.71);
    
    EXPECT_TRUE(v.has_item(3.14));
    EXPECT_FALSE(v.has_item(1.41));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
