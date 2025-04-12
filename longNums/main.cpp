#include <iostream>

#include "long_number.hpp"

int main()
{
    pda::LongNumber a {"2000"};
    pda::LongNumber b {"400"};
    std:: cout << (a-b) << std::endl;
    return 0;
}