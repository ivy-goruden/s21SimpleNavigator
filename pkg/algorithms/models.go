package algoritms

import "app/pkg/graph"

type GraphAlgorithms interface {
	DepthFirstSearch(graph *graph.Graph, start_vertex int) []int
	BreadthFirstSearch(graph *graph.Graph, start_vertex int) []int
	GetShortestPathBetweenVertices(graph *graph.Graph, vertex1 int, vertex2 int) int
	GetShortestPathsBetweenAllVertices(graph *graph.Graph) *graph.Graph_Matrix
	GetLeastSpanningTree(graph *graph.Graph) *graph.Graph_Matrix
	SolveTravelingSalesmanProblem(graph *graph.Graph) TsmResult
}

type TsmResult struct {
	Vertices []int   // an array with the route you are looking for (with the vertex traverse order)
	Distance float64 // the length of this route
}

type Algorithm struct{}
