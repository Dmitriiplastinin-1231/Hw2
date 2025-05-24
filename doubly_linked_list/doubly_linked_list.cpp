// doubly_linked_list.cpp

#include "doubly_linked_list.hpp"
#include <iostream>

using biv::DoublyLinkedList;

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    // Удаляем все узлы, проходя по списку
    Node* node = begin;
    while (node) {
        Node* nxt = node->next;
        delete node;
        node = nxt;
    }
}

template<typename T>
std::size_t DoublyLinkedList<T>::get_size() const noexcept {
    return size;
}

template<typename T>
bool DoublyLinkedList<T>::has_item(const T& value) const noexcept {
    // Проходим по всем узлам и сравниваем значение
    for (Node* iter = begin; iter; iter = iter->next) {
        if (iter->value == value) {
            return true;
        }
    }
    return false;
}

template<typename T>
void DoublyLinkedList<T>::print() const noexcept {
    std::cout << "[";
    // Печатаем значения с разделителем "<->"
    for (Node* iter = begin; iter; iter = iter->next) {
        std::cout << iter->value;
        if (iter->next) {
            std::cout << " <-> ";
        }
    }
    std::cout << "]" << std::endl;
}

template<typename T>
void DoublyLinkedList<T>::push_back(const T& value) {
    // Создаём новый узел и корректируем связи
    Node* new_node = new Node(value);
    new_node->prev = end;
    if (end) {
        end->next = new_node;
    } else {
        begin = new_node;
    }
    end = new_node;
    ++size;
}

template<typename T>
bool DoublyLinkedList<T>::remove_first(const T& value) noexcept {
    // Ищем первый узел с таким значением
    for (Node* iter = begin; iter; iter = iter->next) {
        if (iter->value == value) {
            Node* left  = iter->prev;
            Node* right = iter->next;
            // Переподвешиваем соседей
            if (left)  left->next = right;
            else       begin = right;
            if (right) right->prev = left;
            else       end   = left;
            delete iter;
            --size;
            return true;
        }
    }
    return false;
}

