package graph

import (
	"testing"
)

func TestCreateGraph(t *testing.T) {
	graphM := &Graph{}
	rows := 3
	cols := 3
	matrix := make([][]int, rows)
	for i := 0; i < rows; i++ {
		matrix[i] = make([]int, cols)
	}
	matrix[0][1] = 1
	matrix[2][0] = 1
	matrix[1][0] = 1
	matrix[0][2] = 1
	graph := graphM.CreateGraph(matrix)
	f := 1
	s := 2
	err := graph.AddEdge(f, s, 1, false)
	if err != nil {
		t.Error(err.Error())
	}
	f = 3
	s = 1
	err = graph.AddEdge(f, s, 1, false)
	if err != nil {
		t.Error(err.Error())
	}
	if graph.GetLenght() != 3 {
		t.Errorf(`Want = %d, Have = %d`, 3, graph.GetLenght())
	}
	if !graph.GetPaths().Equal(matrix) {
		t.Errorf(`Want = %v, Have = %v`, matrix, graph.GetPaths())
	}
}

func TestCreateGraphDirectional(t *testing.T) {
	graphM := &Graph{}
	rows := 3
	cols := 3
	matrix := make([][]int, rows)
	for i := 0; i < rows; i++ {
		matrix[i] = make([]int, cols)
	}
	matrix[0][1] = 1
	matrix[2][0] = 1
	graph := graphM.CreateGraph(matrix)
	f := 1
	s := 2
	err := graph.AddEdge(f, s, 1, true)
	if err != nil {
		t.Error(err.Error())
	}
	f = 3
	s = 1
	err = graph.AddEdge(f, s, 1, true)
	if err != nil {
		t.Error(err.Error())
	}
	if graph.HasDirection() {
		t.Errorf(`Want = %s, Have = %s`, "false", "true")
	}
	if !graph.GetPaths().Equal(matrix) {
		t.Errorf(`Want = %v, Have = %v`, matrix, graph.GetPaths())
	}
}
