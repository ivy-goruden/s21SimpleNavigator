package graph

import(
	"errors"
)

var (
    ErrGraphNotFound    = errors.New("graph not found")
    ErrInvalidMatrix    = errors.New("invalid adjacency matrix")
    ErrDuplicateGraph   = errors.New("graph with this name already exists")
    ErrGraphNotLoaded   = errors.New("no graph loaded")
	ErrNoEdge = errors.New("No edge")
)

func NoEdgeError() error {
	return errors.New("Node doesn't exist")
}
