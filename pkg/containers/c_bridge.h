#ifndef C_BRIDGE_H
#define C_BRIDGE_H

#ifdef __cplusplus
extern "C" {
#endif
    // Для очереди
    typedef void* queue_t;
    queue_t queue_new();
    void queue_delete(queue_t q);
    void queue_push(queue_t q, int value);
    void queue_pop(queue_t q);
    int queue_front(queue_t q);
    int queue_back(queue_t q);
    int queue_is_empty(queue_t q);
    int queue_size(queue_t q);

    // Для стека
    typedef void* s21_stack_t;
    s21_stack_t stack_new();
    void stack_delete(s21_stack_t s);
    void stack_push(s21_stack_t s, int value);
    void stack_pop(s21_stack_t s);
    int stack_top(s21_stack_t s);
    int stack_is_empty(s21_stack_t s);
    int stack_size(s21_stack_t s);

#ifdef __cplusplus
}
#endif

#endif
