package containers

// #include "c_bridge.h"
import "C"

type Stack struct {
	ptr C.s21_stack_t
}

func NewStack() *Stack {
	return &Stack{ptr: C.stack_new()}
}

func (s *Stack) Len() int {
	return int(C.stack_size(s.ptr))
}

func (s *Stack) Delete() {
	if s.ptr != nil {
		C.stack_delete(s.ptr)
		s.ptr = nil
	}
}

func (s *Stack) Push(value int) {
	C.stack_push(s.ptr, C.int(value))
}

func (s *Stack) Pop() int {
	value := int(C.stack_top(s.ptr))
	C.stack_pop(s.ptr)
	return value
}

func (s *Stack) Top() int {
	return int(C.stack_top(s.ptr))
}

func (s *Stack) IsEmpty() bool {
	return C.stack_is_empty(s.ptr) != 0
}
