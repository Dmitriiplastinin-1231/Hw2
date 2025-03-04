#include <iostream>

#include "main.hpp"
#include "./lib/hoartSort.hpp"


int main() 
{
    int size_arr;
    std::cin >> size_arr;
    int arr[size_arr];
    
    fill(arr, size_arr);
    hoart::sort(arr, size_arr);

    for (int i = 0; size_arr > i; i++){
        std::cout << arr[i];
    }
    

    return 0;
}

void fill(int* arr, const int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cin >> arr[i];
    }
}