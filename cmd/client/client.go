package main

import (
	algorithms "app/pkg/algorithms"
	"app/pkg/graph"
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	var g *graph.Graph
	alg := &algorithms.Algorithm{}

	for {
		printMenu()
		fmt.Print("Enter choice: ")
		choiceStr, _ := reader.ReadString('\n')
		choiceStr = strings.TrimSpace(choiceStr)
		choice, err := strconv.Atoi(choiceStr)
		if err != nil {
			fmt.Println("Invalid input, please enter a number.")
			continue
		}

		switch choice {
		case 1:
			fmt.Print("Enter filename: ")
			filename, _ := reader.ReadString('\n')
			filename = strings.TrimSpace(filename)
			newGraph := graph.NewGraph()
			err := newGraph.LoadGraphFromFile(filename)
			if err != nil {
				fmt.Printf("Error loading graph: %v\n", err)
			} else {
				g = newGraph
				fmt.Println("Graph loaded successfully.")
			}
		case 2:
			if g == nil {
				fmt.Println("Graph not loaded.")
				continue
			} else {
				m := g.GetPaths()
				printMatrix(&m)
			}
			fmt.Print("Enter start vertex: ")
			startStr, _ := reader.ReadString('\n')
			start, _ := strconv.Atoi(strings.TrimSpace(startStr))
			result := alg.BreadthFirstSearch(g, start)
			fmt.Printf("BFS result: %v\n", result)
		case 3:
			if g == nil {
				fmt.Println("Graph not loaded.")
				continue
			} else {
				m := g.GetPaths()
				printMatrix(&m)
			}
			fmt.Print("Enter start vertex: ")
			startStr, _ := reader.ReadString('\n')
			start, _ := strconv.Atoi(strings.TrimSpace(startStr))
			result := alg.DepthFirstSearch(g, start)
			fmt.Printf("DFS result: %v\n", result)
		case 4:
			if g == nil {
				fmt.Println("Graph not loaded.")
				continue
			} else {
				m := g.GetPaths()
				printMatrix(&m)
			}
			fmt.Print("Enter start vertex: ")
			startStr, _ := reader.ReadString('\n')
			start, _ := strconv.Atoi(strings.TrimSpace(startStr))
			fmt.Print("Enter end vertex: ")
			endStr, _ := reader.ReadString('\n')
			end, _ := strconv.Atoi(strings.TrimSpace(endStr))
			result := alg.GetShortestPathBetweenVertices(g, start, end)
			fmt.Printf("Shortest path length: %d\n", result)
		case 5:
			if g == nil {
				fmt.Println("Graph not loaded.")
				continue
			} else {
				m := g.GetPaths()
				printMatrix(&m)
			}
			result := alg.GetShortestPathsBetweenAllVertices(g)
			fmt.Println("Shortest paths matrix:")
			printMatrix(result)
		case 6:
			if g == nil {
				fmt.Println("Graph not loaded.")
				continue
			} else {
				m := g.GetPaths()
				printMatrix(&m)
			}
			result := alg.GetLeastSpanningTree(g)
			fmt.Println("Minimum Spanning Tree matrix:")
			printMatrix(result)
		case 7:
			if g == nil {
				fmt.Println("Graph not loaded.")
				continue
			} else {
				m := g.GetPaths()
				printMatrix(&m)
			}
			result := alg.SolveTravelingSalesmanProblem(g)
			fmt.Printf("TSP Result: Path: %v, Distance: %f\n", result.Vertices, result.Distance)
		case 0:
			fmt.Println("Exiting...")
			return
		default:
			fmt.Println("Invalid choice.")
		}
		fmt.Println()
	}
}

func printMenu() {
	fmt.Println("=== SimpleNavigator Menu ===")
	fmt.Println("1. Load graph from file(in src folder)")
	fmt.Println("2. Breadth First Search (BFS)")
	fmt.Println("3. Depth First Search (DFS)")
	fmt.Println("4. Shortest path between two vertices")
	fmt.Println("5. Shortest paths between all pairs")
	fmt.Println("6. Minimum Spanning Tree")
	fmt.Println("7. Traveling Salesman Problem (TSP)")
	fmt.Println("0. Exit")
}

func printMatrix(matrix *graph.Graph_Matrix) {
	if matrix == nil {
		fmt.Println("Result is nil")
		return
	}
	mat := *matrix
	for _, row := range mat {
		for _, val := range row {
			fmt.Printf("%d ", val)
		}
		fmt.Println()
	}
}
