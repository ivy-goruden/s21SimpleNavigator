#ifndef S21_QUEUE_H
#define S21_QUEUE_H

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
class queue {
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
    queue() {
        head = nullptr;
        tail = nullptr;
    }
    
    queue(std::initializer_list<T> const& items) {
        head = new Node(*(items.begin()));
        Node* temp = head;

        for (auto it = items.begin() + 1; it != items.end(); it++) {
            Node* new_node = new Node(*it);
            temp->next = new_node;
            tail = new_node;
            temp = temp->next;
        }
    }

    // copy
    queue(const queue& q) {
        if (q.head == nullptr) return;
        head = new Node(q.head->value);
        tail = head;
        Node* src_current = q.head->next;
        Node* dst_current = head;

        while (src_current != nullptr) {
            dst_current->next = new Node(src_current->value);
            dst_current = dst_current->next;
            tail = dst_current;
            src_current = src_current->next;
        }
    }  
    
    // move
    queue(queue&& q) {
        this->head = q.head;
        this->tail = q.tail;
        q.head = q.tail = nullptr;
    }

    // destructor
    ~queue() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // move
    queue<T>& operator=(queue&& q) {
        if (this != &q) {
            this->head = q.head;
            this->tail = q.tail;
            q.head = q.tail = nullptr;
        }
        return *this;
    }

    T front() {
        if (empty()) throw std::runtime_error("Queue is empty");
        return (head->value);
    }

    T back() {
        if (empty()) throw std::runtime_error("Queue is empty");
        return (tail->value);
    }

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
        if (!tail) {
            head = tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
        }
    }

    void pop() {
        if (head == nullptr) {
            return;
        }        
        Node* temp = head;
        head = head->next;        
        if (head == nullptr) {
            tail = nullptr;
        }        
        delete temp;
    }

    void swap(queue& other) {
        Node* tempH = head;
        Node* tempT = tail;
        head = other.head;
        tail = other.tail;
        other.head = tempH;
        other.tail = tempT;
    }
};

}  // namespace S21

#endif
