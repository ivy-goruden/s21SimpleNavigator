package graph

func (m1 Graph_Matrix) Equal(m2 Graph_Matrix) bool {
	// Check if dimensions are the same
	if len(m1) != len(m2) {
		return false
	}

	// For each row, check length and contents
	for i := 0; i < len(m1); i++ {
		if len(m1[i]) != len(m2[i]) {
			return false
		}

		// Compare each element in the row
		for j := 0; j < len(m1[i]); j++ {
			if m1[i][j] != m2[i][j] {
				return false
			}
		}
	}

	return true
}

func NewGraphMatrix(n int) *Graph_Matrix {
	newMatrix := make([][]int, n)
	for i := 0; i < n; i++ {
		newMatrix[i] = make([]int, n)
	}
	return (*Graph_Matrix)(&newMatrix)
}
