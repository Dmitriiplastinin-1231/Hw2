#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "long_numbers.hpp"

TEST(ArraysEqual, Аddition) 
{
    pda::LongNumber a {"2000"};
    pda::LongNumber b {"200"};

    pda::LongNumber actual = (a+b);
    pda::LongNumber expected {"2200"};

    ASSERT_EQ(actual, expected)
        << "ожидаемое значение при сложение: "
        << expected
        << " получаемое: "
        << actual;
}
TEST(ArraysEqual, Multiplication) 
{
    pda::LongNumber a {"2000"};
    pda::LongNumber b {"20"};

    pda::LongNumber actual = (a * b);
    pda::LongNumber expected {"40000"};

    ASSERT_EQ(actual, expected)
        << "ожидаемое значение при умножение: "
        << expected
        << " получаемое: "
        << actual;
}
TEST(ArraysEqual, Devision) 
{
    pda::LongNumber a {"2000"};
    pda::LongNumber b {"20"};

    pda::LongNumber actual = (a / b);
    pda::LongNumber expected {"100"};

    ASSERT_EQ(actual, expected)
        << "ожидаемое значение при деление: "
        << expected
        << " получаемое: "
        << actual;
}
TEST(ArraysEqual, RemaindDivision) 
{
    pda::LongNumber a {"2000"};
    pda::LongNumber b {"20"};

    pda::LongNumber actual = (a % b);
    pda::LongNumber expected {"0"};

    ASSERT_EQ(actual, expected)
        << "ожидаемое значение при получение остатка от деления: "
        << expected
        << " получаемое: "
        << actual;
}
TEST(ArraysEqual, Comparing) 
{
    pda::LongNumber a {"2000"};
    pda::LongNumber b {"20"};

    bool actual = (a > b);
    bool expected{1};

    ASSERT_EQ(actual, expected)
        << "ожидаемое значение при >: "
        << expected
        << " получаемое: "
        << actual;
}


int main(int argc, char** argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
