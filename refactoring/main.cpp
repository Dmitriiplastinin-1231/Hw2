#include <iostream>

int fillArr (int* arr, const int size);
void printArr (const int* const arr, const int size);
float midNum (const int sumArr, const int arraySize);

int main() 
{
    const int arraySize = 10;

    for (int i = 1; i < 4; i++) 
    {
        int arr[arraySize];

        std::cout << i << " последоваетельность:" << std::endl;
        int sumArr = fillArr(arr, arraySize);
        printArr(arr, arraySize);

        std::cout 
            << "Среднее " << i << " последовательности = " 
            << midNum(sumArr, arraySize) 
            << std::endl;
    }


    return 0;
}

int fillArr (int* arr, const int size) 
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 10;
        sum = sum + arr[i];
    }
    return sum;
}

void printArr (const int* const arr, const int size) 
{
    static char format = ' ';
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i];
        std::cout << format;
    }
    std::cout << ' ' << std::endl;
}

float midNum (const int sumArr, const int arraySize) 
{
    return (1.0 * sumArr / arraySize);
}


