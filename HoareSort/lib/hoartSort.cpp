#include <iostream>

#include "hoartSort.hpp"

namespace hoart
{
    static int __partOfSort(int* arr, int l, int r);
    static void __hoartSort(int* arr, int l, int r);


    void sort(int* arr, const int size) 
    {
        __hoartSort(arr, 0, size-1);
    }

    int __partOfSort(int* arr, int l, int r)
    {
        int pilot = arr[(l + r) / 2];
        while (l <= r)
        {
            while (arr[l] < pilot) l++;
            while (arr[r] > pilot) r--;

            if (l <= r)
            {
                int temp = arr[l];
                arr[l] = arr[r];
                arr[r] = temp;
                l++;
                r--;
            }
        }

        return l;
    }

    void __hoartSort(int* arr, int l, int r)
    {
        if (l>=r) return;

        int res = __partOfSort(arr, l, r);
        __hoartSort(arr, l, res-1);
        __hoartSort(arr, res, r);
    }
}


