package algoritms

import (
	"app/pkg/graph"
	"math/rand/v2"
)

func contains(stash []int, needle int) bool {
	for i := range stash {
		if stash[i] == needle {
			return true
		}
	}
	return false
}

type IntSlice []int

func (s IntSlice) Len() int {
	return len(s)
}

func (s IntSlice) Less(i, j int) bool {
	return s[i] > s[j]
}

func (s IntSlice) Swap(i, j int) {
	s[i], s[j] = s[j], s[i]
}

func getNextNode(neighs []float64, visited []int) int { //вершина - вес
	sum := 0.0
	last := visited[len(visited)-1]
	for i, v := range neighs {
		node := i + 1
		if node == last || contains(visited, node) || v <= 0 {
			continue
		}
		sum += v
	}
	if sum == 0 {
		return -1
	}
	probability := rand.Float64() * sum
	edgeValue := 0.0
	for i, v := range neighs {
		node := i + 1
		if node == last || contains(visited, node) || v <= 0 {
			continue
		}
		edgeValue += v
		if probability < edgeValue {
			return node
		}
	}
	return -1
}

func IsConnected(g *graph.Graph) bool {
	alg := &Algorithm{}
	visited := alg.DepthFirstSearch(g, 1)
	return len(visited) == g.GetLenght()
}

func IsComplete(g *graph.Graph) bool {
	paths := g.GetPaths()
	for i := 0; i < g.GetLenght(); i++ {
		for x := 0; x < g.GetLenght(); x++ {
			if paths[i][x] == 0 && i != x {
				return false
			}
		}
	}
	return true
}

func IsWeak(g *graph.Graph) bool {
	paths := g.GetPaths()
	for i := 0; i < g.GetLenght(); i++ {
		for x := 0; x < g.GetLenght(); x++ {
			if paths[i][x] < 0 {
				return true
			}
		}
	}
	return false
}
