package graph

import (
	"bufio"
	"errors"
	"fmt"
	"os"
	"path/filepath"
	"slices"
	"strconv"
	"strings"
)

func (matrix *Graph_Matrix) len() int {
	return len(*matrix)
}

func NewGraph() *Graph {
	return &Graph{}
}

func (graph *Graph) CreateGraph(paths Graph_Matrix) *Graph {
	new_graph := &Graph{}
	n := len(paths)
	newPaths := make(Graph_Matrix, n)
	for i := 0; i < n; i++ {
		newPaths[i] = make([]int, n)
		copy(newPaths[i], paths[i])
	}
	new_graph.paths = newPaths
	new_graph.lenght = n
	return new_graph
}

func (graph *Graph) AddEdge(a int, b int, weight int, hasDirection bool) error {
	if graph.paths == nil {
		return errors.New("graph not initialized (paths is nil)")
	}
	weight = max(1, weight)
	paths := graph.paths
	if a < 1 || a > graph.GetLenght() {
		return NoEdgeError()
	}
	if b < 1 || b > graph.GetLenght() {
		return NoEdgeError()
	}
	paths[a-1][b-1] = weight
	if !hasDirection {
		paths[b-1][a-1] = weight
	}
	return nil
}

func (graph *Graph) GetLenght() int {
	return len(graph.paths)
}

func (graph *Graph) GetPaths() Graph_Matrix {
	return graph.paths
}

type verticesReader string

func (r verticesReader) Read() (int, error) {
	num, err := strconv.Atoi(string(r))
	if err != nil {
		return 0, err
	}
	return num, nil
}

type rowReader string

func (r rowReader) Read() ([]int, error) {
	parts := strings.Fields(string(r))
	nums := make([]int, 0, len(parts))
	for _, p := range parts {
		n, err := strconv.Atoi(p)
		if err != nil {
			return nil, errors.New("convert row number error")
		}
		nums = append(nums, n)
	}
	return nums, nil
}

func (g *Graph) HasDirection() bool {
	dir := true
	for i, row := range g.paths {
		for j := range row {
			if i != j && g.paths[i][j] != g.paths[j][i] {
				return false
			}
		}
	}
	return dir
}

func (g *Graph) LoadGraphFromFile(filename string) error {
	fullPath := filepath.Join("", filename)
	file, err := os.Open(fullPath)
	if err != nil {
		fmt.Println(err)
		return err
	}
	defer file.Close()

	sc := bufio.NewScanner(file)
	if sc.Scan() {
		num, err := verticesReader(sc.Text()).Read()
		if err != nil {
			return err
		}
		g.lenght = num
	} else {
		return errors.New("no number veritices found")
	}

	g.paths = make([][]int, 0)
	for i := 0; i < g.lenght; i++ {
		if sc.Scan() {
			nums, err := rowReader(sc.Text()).Read()
			if err != nil {
				return err
			}
			g.paths = append(g.paths, nums)
		} else {
			return errors.New("scan row error")
		}
	}
	return nil
}

func (g *Graph) ExportGraphToDot(name, filename string) error {
	dir := g.HasDirection()
	ed := make([]string, 0)
	for i := 1; i <= g.lenght; i++ {
		i_str := fmt.Sprint(i)
		if !slices.Contains(ed, i_str) {
			ed = append(ed, i_str)
		}
	}
	for i, row := range g.paths {
		for j, item := range row {
			first := i + 1
			second := j + 1
			arr := "->"
			if !dir {
				first = min(i, j) + 1
				second = max(i, j) + 1
				arr = "--"
			}
			if item != 0 {
				ed_str := fmt.Sprintf("%d %s %d", first, arr, second)
				if !slices.Contains(ed, ed_str) {
					ed = append(ed, ed_str)
				}
			}
		}
	}

	var out strings.Builder
	fmt.Fprintf(&out, "graph %s {\n", strings.ReplaceAll(name, ".", "_"))
	for _, v := range ed {
		fmt.Fprintf(&out, "    %s;\n", v)
	}
	out.WriteString("}\n")

	fullPath := filepath.Join("", filename)
	file, err := os.Create(fullPath)
	if err != nil {
		return err
	}
	defer file.Close()

	_, err = file.WriteString(out.String())

	return err
}
