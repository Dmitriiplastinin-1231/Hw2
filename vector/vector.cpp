#include "vector.hpp"
#include <iostream>
#include <algorithm>  

using biv::Vector;


template <typename T>
const std::size_t Vector<T>::START_CAPACITY = 10;

template <typename T>
Vector<T>::Vector()
    : arr(new T[START_CAPACITY])
    , capacity(START_CAPACITY)
    , size(0)
{ }

template <typename T>
Vector<T>::~Vector() {
    delete[] arr;
}

template <typename T>
std::size_t Vector<T>::get_size() const noexcept {
    return size;
}

template <typename T>
bool Vector<T>::has_item(const T& value) const noexcept {
    return std::find(arr, arr + size, value) != arr + size;
}

template <typename T>
bool Vector<T>::insert(const std::size_t index, const T& value) {
    if (index > size) {
        return false;
    }
    if (size == capacity) {
        const std::size_t newCap = capacity ? capacity * 2 : 1;
        T* buffer = new T[newCap];
        std::copy(arr, arr + index, buffer);

        buffer[index] = value;
        std::copy(arr + index, arr + size, buffer + index + 1);
        delete[] arr;
        arr = buffer;
        capacity = newCap;
    } else {
        std::copy_backward(arr + index, arr + size, arr + size + 1);
        arr[index] = value;
    }

    ++size;
    return true;
}

template <typename T>
void Vector<T>::push_back(const T& value) {
    if (size == capacity) {
        const std::size_t newCap = capacity ? capacity * 2 : 1;
        T* buffer = new T[newCap];
        std::copy(arr, arr + size, buffer);
        delete[] arr;
        arr = buffer;
        capacity = newCap;
    }
    arr[size++] = value;
}

template <typename T>
bool Vector<T>::remove_first(const T& value) {
    T* found = std::find(arr, arr + size, value);
    if (found == arr + size) {
        return false;
    }
    std::move(found + 1, arr + size, found);
    --size;
    return true;
}

template <typename T>
void Vector<T>::print() const noexcept {
    std::cout << '[';
    for (std::size_t i = 0; i < size; ++i) {
        std::cout << arr[i];
        if (i + 1 < size) {
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
}

