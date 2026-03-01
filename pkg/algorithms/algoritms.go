package algoritms

import (
	"app/pkg/containers"
	"app/pkg/graph"
	"math"
	"math/rand/v2"
	"slices"
	"sort"
)

// *нерекурентный* поиск в глубину в графе от заданной вершины. Функция должна возвращать массив,
// содержащий в себе обойдённые вершины в порядке их обхода.
func (algoritm *Algorithm) DepthFirstSearch(g *graph.Graph, start_vertex int) []int {
	visited := make([]int, 0)
	to_visit := containers.NewStack()
	to_visit.Push(start_vertex)
	for to_visit.Len() > 0 {
		ind := to_visit.Pop()
		if slices.Contains(visited, ind) {
			continue
		}
		visited = append(visited, ind)
		nodes := g.GetPaths()[ind-1]
		for i := 1; i <= len(nodes); i++ {
			node := nodes[i-1]
			if node != 0 && !slices.Contains(visited, i) {
				to_visit.Push(i)
			}
		}
	}
	return visited
}

// поиск в ширину в графе от заданной вершины. Функция должна возвращать массив,
// содержащий в себе обойдённые вершины в порядке их обхода.
func (algoritm *Algorithm) BreadthFirstSearch(g *graph.Graph, start_vertex int) []int {
	visited := make([]int, 0)
	to_visit := containers.NewQueue()
	to_visit.Push(start_vertex)
	for to_visit.Len() > 0 {
		ind := to_visit.Pop()
		if slices.Contains(visited, ind) {
			continue
		}
		visited = append(visited, ind)
		nodes := g.GetPaths()[ind-1]
		for i := 1; i <= len(nodes); i++ {
			node := nodes[i-1]
			if node != 0 && !slices.Contains(visited, i) {
				to_visit.Push(i)
			}
		}
	}
	return visited
}

// поиск кратчайшего пути между двумя вершинами в графе с использованием *алгоритма Дейкстры*.
// Функция принимает на вход номера двух вершин и возвращает численный результат, равный наименьшему расстоянию между ними.
func (algoritm *Algorithm) GetShortestPathBetweenVertices(graph *graph.Graph, vertex1 int, vertex2 int) int {
	visited := make([]int, 0)
	visited = append(visited, vertex1)
	return getPathToVertex(graph, vertex2, visited)

}

func getPathToVertex(graph *graph.Graph, vertex2 int, visited []int) int {
	cur_node := visited[len(visited)-1]
	if cur_node == vertex2 {
		return getLenght(graph, visited)
	}
	paths := make([]int, 0)
	nodes := graph.GetPaths()[cur_node-1]
	for idx, node := range nodes {
		if node != 0 && !contains(visited, idx+1) {
			path := getPathToVertex(graph, vertex2, append(visited, idx+1))
			if path != -1 {
				paths = append(paths, path)
			}
		}
	}
	if len(paths) > 0 {
		sort.Ints(paths)
		return paths[0]
	}
	return -1
}

func getLenght(g *graph.Graph, visited []int) int {
	lenght := 0
	matrix := g.GetPaths()
	for i := 0; i < len(visited)-1; i++ {
		lenght += matrix[visited[i]-1][visited[i+1]-1]
	}
	return lenght
}

// поиск кратчайших путей между всеми парами вершин в графе с использованием *алгоритма Флойда-Уоршелла*.
// В качестве результата функция возвращает матрицу кратчайших путей между всеми вершинами графа.
func (algoritm *Algorithm) GetShortestPathsBetweenAllVertices(g *graph.Graph) *graph.Graph_Matrix {
	var new_matrix graph.Graph_Matrix
	new_matrix = make([][]int, g.GetLenght())
	for i := 0; i < g.GetLenght(); i++ {
		new_matrix[i] = make([]int, g.GetLenght())
		for x := 0; x < g.GetLenght(); x++ {
			new_matrix[i][x] = algoritm.GetShortestPathBetweenVertices(g, i+1, x+1)
		}
	}
	return &new_matrix
}

// поиск наименьшего остовного дерева в графе с помощью *алгоритма Прима* (Prim's algorithm).
// В качестве результата функция должна возвращать матрицу смежности для минимального остовного дерева.
func (algoritm *Algorithm) GetLeastSpanningTree(g *graph.Graph) *graph.Graph_Matrix {
	size := g.GetLenght()
	X := make([]int, size)
	X = append(X, 1)
	T := make([]Edge, 0)

	if size > 0 {
		eds := edges(g)
		for {
			ceds := closestEdges(eds, X)
			if len(ceds) == 0 {
				break
			}
			if med, ok := minCostEdge(ceds); ok {
				T = append(T, med)
				if !slices.Contains(X, med.w) {
					X = append(X, med.w)
				} else {
					X = append(X, med.v)
				}
			}
		}
	}

	return edgeListToMatrix(T)
}

type Edge struct {
	v, w, c int
}

type EdgeList []Edge

func edgeListToMatrix(e EdgeList) *graph.Graph_Matrix {
	esize := len(e)
	size := esize + 1
	var new_matrix graph.Graph_Matrix = make([][]int, size)
	for i := range size {
		new_matrix[i] = make([]int, size)
	}
	for ei := range esize {
		i := e[ei].v - 1
		j := e[ei].w - 1
		new_matrix[i][j] = e[ei].c
		new_matrix[j][i] = e[ei].c
	}
	return &new_matrix
}

func edges(g *graph.Graph) EdgeList {
	var l EdgeList = make([]Edge, 0)
	m := g.GetPaths()
	size := g.GetLenght()
	for i := range size {
		for j := i; j < size; j++ {
			if m[i][j] > 0 {
				l = append(l, Edge{v: i + 1, w: j + 1, c: m[i][j]})
			}
		}
	}
	return l
}

func closestEdges(el EdgeList, X []int) EdgeList {
	var l EdgeList = make([]Edge, 0)
	for i := range len(el) {
		if (slices.Contains(X, el[i].v) && !slices.Contains(X, el[i].w)) ||
			(!slices.Contains(X, el[i].v) && slices.Contains(X, el[i].w)) {
			l = append(l, el[i])
		}
	}
	return l
}

func minCostEdge(el EdgeList) (Edge, bool) {
	if len(el) == 0 {
		return Edge{}, false
	}
	mi := 0
	mc := el[mi].c
	for i := range len(el) {
		if mc > el[i].c {
			mc = el[i].c
			mi = i
		}
	}
	return el[mi], true
}

type AntPath struct {
	path   []int
	length float64
}

func (algoritm *Algorithm) SolveTravelingSalesmanProblem(g *graph.Graph) TsmResult {
	if !IsConnected(g) {
		return TsmResult{}
	}
	if !IsComplete(g) {
		newMatrix := algoritm.GetShortestPathsBetweenAllVertices(g)
		g = g.CreateGraph(*newMatrix)
	}
	if IsWeak(g) {
		return TsmResult{}
	}
	paths := g.GetPaths()
	n := len(paths)
	pheromones := make([][]float64, n)
	for i := 0; i < n; i++ {
		pheromones[i] = make([]float64, n)
		for j := 0; j < n; j++ {
			pheromones[i][j] = 1.0 //инициализация феромонов
		}
	}
	ANTS := 10         //муравьи за раунд
	ROUNDS := 10       //раунды
	EVAPORATION := 0.2 //коэффициэнт испарения
	PHEROMONE := 100.0 //феромоны на ребро при успешном нахождении пути

	var bestPath []int
	minDistance := math.Inf(1)

	for r := 0; r < ROUNDS; r++ {
		var roundPaths []AntPath

		for a := 0; a < ANTS; a++ {
			antPath := AntRun(g, pheromones)
			roundPaths = append(roundPaths, antPath)
		}

		for i := 0; i < n; i++ {
			for j := 0; j < n; j++ {
				pheromones[i][j] *= (1.0 - EVAPORATION)
				pheromones[i][j] = math.Max(0.1, pheromones[i][j])
			}
		}

		for _, ant := range roundPaths {
			delta := PHEROMONE / ant.length
			for k := 0; k < len(ant.path)-1; k++ {
				u, v := ant.path[k]-1, ant.path[k+1]-1
				pheromones[u][v] += delta
			}
			if ant.length < minDistance {
				minDistance = ant.length
				bestPath = ant.path
			}
		}
	}

	return TsmResult{Vertices: bestPath, Distance: minDistance}
}

func AntRun(g *graph.Graph, pheromones [][]float64) AntPath {
	n := len(pheromones)

	visited := make([]int, 0, n+1)
	current := rand.IntN(n) + 1
	start := current
	visited = append(visited, current)
	for len(visited) < len(pheromones) {
		neighs := pheromones[current-1]
		nextNode := getNextNode(neighs, visited)
		visited = append(visited, nextNode)
		current = nextNode
	}
	visited = append(visited, start)

	return AntPath{
		visited,
		float64(getLenght(g, visited)),
	}

}
