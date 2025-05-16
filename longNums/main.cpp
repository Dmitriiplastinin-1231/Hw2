#include <iostream>

#include "long_number.hpp"

int main()
{
    pda::LongNumber a {"2000"};
    pda::LongNumber b {"200"};
    pda::LongNumber c {"-3"};

    std:: cout << ((a + b)) << std::endl;
    std:: cout << ((a - b)) << std::endl;
    std:: cout << ((b*c)) << std::endl;
    std:: cout << ((a * b)) << std::endl;
    // std:: cout << (a / (b)) << std::endl;
    return 0;
}