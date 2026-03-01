#include "c_bridge.h"

#include "../cpp_containers/s21_queue.h"  // наши C++ классы
#include "../cpp_containers/s21_stack.h"  // наши C++ классы

// Очередь
extern "C" {

    queue_t queue_new() {
        return new S21::queue<int>();
    }

    void queue_delete(queue_t q) {
        delete static_cast<S21::queue<int>*>(q);
    }

    void queue_push(queue_t q, int value) {
        static_cast<S21::queue<int>*>(q)->push(value);
    }

    void queue_pop(queue_t q) {
        static_cast<S21::queue<int>*>(q)->pop();
    }

    int queue_front(queue_t q) {
        return static_cast<S21::queue<int>*>(q)->front();
    }

    int queue_back(queue_t q) {
        return static_cast<S21::queue<int>*>(q)->back();
    }

    int queue_is_empty(queue_t q) {
        return static_cast<S21::queue<int>*>(q)->empty() ? 1 : 0;
    }

    int queue_size(queue_t q) {
        return static_cast<S21::queue<int>*>(q)->size();
    }

    // Стек
    s21_stack_t stack_new() {
        return new S21::stack<int>();
    }

    void stack_delete(s21_stack_t s) {
        delete static_cast<S21::stack<int>*>(s);
    }

    void stack_push(s21_stack_t s, int value) {
        static_cast<S21::stack<int>*>(s)->push(value);
    }

    void stack_pop(s21_stack_t s) {
        static_cast<S21::stack<int>*>(s)->pop();
    }

    int stack_top(s21_stack_t s) {
        return static_cast<S21::stack<int>*>(s)->top();
    }

    int stack_is_empty(s21_stack_t s) {
        return static_cast<S21::stack<int>*>(s)->empty() ? 1 : 0;
    }

    int stack_size(s21_stack_t s) {
        return static_cast<S21::stack<int>*>(s)->size();
    }

}
