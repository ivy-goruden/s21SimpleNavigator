#ifndef S21_STACK_H
#define S21_STACK_H

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <list>
#include <regex>
#include <stdexcept>
#include <string>
#include <utility>

namespace S21 {

template <typename T>
class stack {
    using size_type = size_t;

   private:
    struct Node {
        T value;
        Node* next;
        Node(const T& val) : value(val), next(nullptr) {}
    };
    Node* head = nullptr;
    Node* tail = nullptr;

   public:
    stack() {
        head = nullptr;
        tail = nullptr;
    }

    stack(std::initializer_list<T> const& items) {
        head = new Node(*(items.begin()));
        tail = new Node(*(items.begin()));

        for (auto it = items.begin() + 1; it != items.end(); it++) {
            Node* new_node = new Node(*it);
            new_node->next = head;
            head = new_node;
        }
    }

    // copy
    stack(const stack& q) {
        if (q.head == nullptr) return;
        head = new Node(q.head->value);
        Node* src_current = q.head->next;
        Node* dst_current = head;

        while (src_current != nullptr) {
            dst_current->next = new Node(src_current->value);
            dst_current = dst_current->next;
            src_current = src_current->next;
        }
    }

    // move
    stack(stack&& q) {
        head = q.head;
        tail = q.tail;
    }

    // destructor
    ~stack() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // move
    stack<T>& operator=(stack&& q) {
        head = q.head;
        tail = q.tail;
        return *this;
    }

    T top() {
        if (empty()) throw std::runtime_error("Queue is empty");
        return (head->value);
    };

    bool empty() {
        if (head != nullptr) {
            return false;
        } else {
            return true;
        }
    }

    size_type size() {
        int num = 0;
        Node* src = head;
        while (src != nullptr) {
            num++;
            src = src->next;
        }
        return num;
    }

    void push(const T value) {
        Node* temp = new Node(value);
        temp->next = head;
        head = temp;
    }

    void pop() {
        if (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void swap(stack& other) {
        Node* tempH = head;
        head = other.head;
        other.head = tempH;
    }
};

}  // namespace S21

#endif
