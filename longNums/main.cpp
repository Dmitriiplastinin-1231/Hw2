#include <iostream>

#include "long_number.hpp"

int main()
{
    naa::LongNumber a {"2000"};
    naa::LongNumber b {"400"};
    naa::LongNumber c {"-1"};

    std:: cout << (a / (b)) << std::endl;
    return 0;
}