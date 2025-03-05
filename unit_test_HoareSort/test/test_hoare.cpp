#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "hoare_sort.hpp"

TEST(ArraysEqual, AnyElementsCount) 
{
    const int size = 6;
    int actual[size] = {1,8,2,5,3,11};
    int expected[size] = {1,2,3,5,8,11};

    hoart::sort(actual, size);

    for (int i = 0; i < size; i++)
    {
        ASSERT_EQ(expected[i], actual[i])
            << "Ожидаемый и отсортированный массив отличаются на индексе: "
            << i
            << " значение ожидаемого и отсортированного соответсвенно: "
            << expected[i] << ' ' << actual[i];
    }
}

int main(int argc, char** argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}