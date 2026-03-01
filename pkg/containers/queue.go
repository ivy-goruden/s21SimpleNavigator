package containers

/*
#include "c_bridge.h"
*/
import "C"

// Queue представляет обёртку над C++ очередью.
type Queue struct {
	ptr C.queue_t
}

// NewQueue создаёт новую очередь.
func NewQueue() *Queue {
	return &Queue{ptr: C.queue_new()}
}

func (s *Queue) Len() int {
	return int(C.queue_size(s.ptr))
}

// Delete освобождает ресурсы очереди. Должен быть вызван для каждого созданного объекта.
func (q *Queue) Delete() {
	if q.ptr != nil {
		C.queue_delete(q.ptr)
		q.ptr = nil
	}
}

// Push добавляет элемент в конец очереди.
func (q *Queue) Push(value int) {
	C.queue_push(q.ptr, C.int(value))
}

// Pop удаляет и возвращает первый элемент очереди.
func (q *Queue) Pop() int {
	value := int(C.queue_front(q.ptr))
	C.queue_pop(q.ptr)
	return value
}

// Front возвращает первый элемент без удаления.
func (q *Queue) Front() int {
	return int(C.queue_front(q.ptr))
}

// Back возвращает последний элемент без удаления.
func (q *Queue) Back() int {
	return int(C.queue_back(q.ptr))
}

// IsEmpty проверяет, пуста ли очередь.
func (q *Queue) IsEmpty() bool {
	return C.queue_is_empty(q.ptr) != 0
}
