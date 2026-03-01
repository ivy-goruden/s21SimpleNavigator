package main

import (
	"app/pkg/containers"
	"fmt"
)

func test_stack() {
	g := containers.NewStack()
	g.Push(1)
	g.Push(2)
	g.Push(3)
	g.Push(4)
	g.Push(5)

	fmt.Printf("glen: %d\n", g.Len())
	len := g.Len()
	for i := 0; i < len; i++ {
		fmt.Printf("g: %d\n", g.Pop())
	}
	fmt.Println()
}

func test_queue() {
	g := containers.NewQueue()
	g.Push(1)
	g.Pop()
	g.Push(2)

	fmt.Printf("glen: %d\n", g.Len())
	len := g.Len()
	fmt.Printf("back: %d\n", g.Back())
	fmt.Printf("front: %d\n", g.Front())
	for i := 0; i < len; i++ {
		fmt.Printf("g: %d\n", g.Pop())
	}
	fmt.Println()
}

func main() {
	test_queue()
	test_stack()
}
