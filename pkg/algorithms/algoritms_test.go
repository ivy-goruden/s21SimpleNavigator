package algoritms

import (
	"app/pkg/graph"
	"math"
	"slices"
	"testing"
)

func TestDepthFirstSearch(t *testing.T) {

	g := graph.NewGraph()
	g.LoadGraphFromFile("tests/allLoopGraph.txt")

	var alg GraphAlgorithms = &Algorithm{}
	result := alg.DepthFirstSearch(g, 6)
	expected := []int{6, 11, 10, 9, 8, 7, 5, 4, 3, 2, 1}
	if !slices.Equal(expected, result) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
}

func TestBreadthFirstSearch(t *testing.T) {
	g := graph.NewGraph()
	g.LoadGraphFromFile("tests/allLoopGraph.txt")
	var alg GraphAlgorithms = &Algorithm{}
	result := alg.BreadthFirstSearch(g, 6)
	expected := []int{6, 1, 2, 3, 4, 5, 7, 8, 9, 10, 11}
	if !slices.Equal(expected, result) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
}

func TestDepthFirstSearchNull(t *testing.T) {

	g := graph.NewGraph()
	g.LoadGraphFromFile("tests/nullGraph.txt")

	var alg GraphAlgorithms = &Algorithm{}
	result := alg.DepthFirstSearch(g, 1)
	expected := []int{1}
	if !slices.Equal(expected, result) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
}

func TestBreadthFirstSearchNull(t *testing.T) {
	g := graph.NewGraph()
	g.LoadGraphFromFile("tests/nullGraph.txt")
	var alg GraphAlgorithms = &Algorithm{}
	result := alg.BreadthFirstSearch(g, 1)
	expected := []int{1}
	if !slices.Equal(expected, result) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
}

func TestDepthFirstSearchDirected(t *testing.T) {

	g := graph.NewGraph()
	g.LoadGraphFromFile("tests/directedGraph.txt")

	var alg GraphAlgorithms = &Algorithm{}
	result := alg.DepthFirstSearch(g, 3)
	expected := []int{3}
	if !slices.Equal(expected, result) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
}

func TestBreadthFirstSearchDirected(t *testing.T) {
	g := graph.NewGraph()
	g.LoadGraphFromFile("tests/directedGraph.txt")
	var alg GraphAlgorithms = &Algorithm{}
	result := alg.BreadthFirstSearch(g, 1)
	expected := []int{1, 2, 3, 5, 4}
	if !slices.Equal(expected, result) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
}

func TestGetShortestPathBetweenVertices(t *testing.T) {
	g := graph.NewGraph()
	g.LoadGraphFromFile("tests/weightedGraph.txt")
	var alg GraphAlgorithms = &Algorithm{}
	result := alg.GetShortestPathBetweenVertices(g, 1, 3)
	expected := 16
	if result != expected {
		t.Errorf("Expected %v, got %v", expected, result)
	}
}

func TestGetShortestPathBetweenVerticesNull(t *testing.T) {
	g := graph.NewGraph()
	g.LoadGraphFromFile("tests/nullGraph.txt")
	var alg GraphAlgorithms = &Algorithm{}
	result := alg.GetShortestPathBetweenVertices(g, 1, 3)
	// If path not found or graph null, it should probably return -1 or handled error.
	// Current implementation returns -1 if not found.
	expected := -1
	if result != expected {
		t.Errorf("Expected %v, got %v", expected, result)
	}
}

func TestGetShortestPathBetweenVerticesWeighted(t *testing.T) {
	g := graph.NewGraph()
	g.LoadGraphFromFile("tests/directedWeightedGraph.txt")
	var alg GraphAlgorithms = &Algorithm{}
	result := alg.GetShortestPathBetweenVertices(g, 2, 3)
	expected := 3
	if result != expected {
		t.Errorf("Expected %v, got %v", expected, result)
	}
}

func TestGetShortestPathsBetweenAllVertices(t *testing.T) {
	g := graph.NewGraph()
	g.LoadGraphFromFile("tests/weightedGraph.txt")
	var alg GraphAlgorithms = &Algorithm{}
	result := alg.GetShortestPathsBetweenAllVertices(g)
	expected := [][]int{{0, 10, 16, 11, 13}, {10, 0, 6, 1, 3}, {16, 6, 0, 5, 3}, {11, 1, 5, 0, 2}, {13, 3, 3, 2, 0}}
	for ind, line := range *result {
		if !slices.Equal(expected[ind], line) {
			t.Errorf("Expected %v, got %v", expected, *result)
		}
	}
}

func TestGetLeastSpanningTree(t *testing.T) {
	g := graph.NewGraph()
	err := g.LoadGraphFromFile("tests/spanningTree.txt")
	if err != nil {
		t.Fatalf("Failed to load graph: %v", err)
	}

	var alg GraphAlgorithms = &Algorithm{}
	result := alg.GetLeastSpanningTree(g)
	expected := [][]int{{0, 10, 0, 0, 0, 0}, {10, 0, 0, 1, 0, 2}, {0, 0, 0, 0, 4, 0}, {0, 1, 0, 0, 3, 0}, {0, 0, 4, 3, 0, 0}, {0, 2, 0, 0, 0, 0}}
	for ind, line := range *result {
		if !slices.Equal(expected[ind], line) {
			t.Errorf("Expected %v, got %v", expected, *result)
		}
	}
}

func TestGetLeastSpanningTree2(t *testing.T) {
	g2 := graph.NewGraph()
	err := g2.LoadGraphFromFile("tests/spanningTree2.txt")
	if err != nil {
		t.Fatalf("Failed to load graph: %v", err)
	}

	var alg GraphAlgorithms = &Algorithm{}
	result2 := alg.GetLeastSpanningTree(g2)
	expected2 := [][]int{{0, 1, 4, 0}, {1, 0, 0, 2}, {4, 0, 0, 0}, {0, 2, 0, 0}}
	for ind, line := range *result2 {
		if !slices.Equal(expected2[ind], line) {
			t.Errorf("Expected %v, got %v", expected2, *result2)
		}
	}
}

func TestGetLeastSpanningTree3(t *testing.T) {
	g := graph.NewGraph()
	err := g.LoadGraphFromFile("tests/spanningTree3.txt")
	if err != nil {
		t.Fatalf("Failed to load graph: %v", err)
	}

	var alg GraphAlgorithms = &Algorithm{}
	result := alg.GetLeastSpanningTree(g)
	expected := [][]int{{0, 2, 0, 0, 0, 0}, {2, 0, 1, 0, 0, 0}, {0, 1, 0, 3, 5, 0}, {0, 0, 3, 0, 0, 8}, {0, 0, 5, 0, 0, 0}, {0, 0, 0, 8, 0, 0}}
	for ind, line := range *result {
		if !slices.Equal(expected[ind], line) {
			t.Errorf("Expected %v, got %v", expected, *result)
		}
	}
}

func TestSolveTravelingSalesmanProblem(t *testing.T) {
	g := graph.NewGraph()
	err := g.LoadGraphFromFile("tests/allLoopGraph.txt")
	if err != nil {
		t.Fatalf("Failed to load graph: %v", err)
	}

	var alg GraphAlgorithms = &Algorithm{}
	result := alg.SolveTravelingSalesmanProblem(g)

	if result.Distance == math.Inf(1) {
		t.Errorf("Expected valid distance, got Inf")
	}
	expectedLen := g.GetLenght() + 1
	if len(result.Vertices) != expectedLen {
		t.Errorf("Expected path length %d, got %d", expectedLen, len(result.Vertices))
	}
	if len(result.Vertices) > 0 && result.Vertices[0] != result.Vertices[len(result.Vertices)-1] {
		t.Errorf("Path does not return to start")
	}
}

func TestSolveTravelingSalesmanProblemNull(t *testing.T) {
	g := graph.NewGraph()
	err := g.LoadGraphFromFile("tests/nullGraph.txt")
	if err != nil {
		t.Fatalf("Failed to load graph: %v", err)
	}

	var alg GraphAlgorithms = &Algorithm{}
	result := alg.SolveTravelingSalesmanProblem(g)

	if len(result.Vertices) != 0 {
		t.Errorf("Expected empty path for null graph, got %v", result.Vertices)
	}
	if result.Distance != 0 {
		t.Errorf("Expected 0 distance for null graph, got %f", result.Distance)
	}
}

func TestSolveTravelingSalesmanProblemDisconnected(t *testing.T) {
	g := graph.NewGraph()
	err := g.LoadGraphFromFile("tests/notConnectedGraph.txt")
	if err != nil {
		t.Fatalf("Failed to load graph: %v", err)
	}

	var alg GraphAlgorithms = &Algorithm{}
	result := alg.SolveTravelingSalesmanProblem(g)

	if len(result.Vertices) != 0 {
		t.Errorf("Expected empty path for disconnected graph, got %v", result.Vertices)
	}
	if result.Distance != 0 {
		t.Errorf("Expected 0 distance for disconnected graph, got %f", result.Distance)
	}
}

func TestSolveTravelingSalesmanProblemDirected(t *testing.T) {
	g := graph.NewGraph()
	err := g.LoadGraphFromFile("tests/directedGraph.txt")
	if err != nil {
		t.Fatalf("Failed to load graph: %v", err)
	}

	var alg GraphAlgorithms = &Algorithm{}
	result := alg.SolveTravelingSalesmanProblem(g)

	if len(result.Vertices) != 0 {
		t.Errorf("Expected empty path for directed graph, got %v", result.Vertices)
	}
	if result.Distance != 0 {
		t.Errorf("Expected 0 distance for directed graph, got %f", result.Distance)
	}
}
