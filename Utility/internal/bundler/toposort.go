package bundler

import (
	"errors"
)

const (
	unvisited int = iota
	visiting
	visited
)

type node interface {
	incoming() []node
}

func toposort(nodes []node) ([]node, error) {
	color := make(map[node]int, len(nodes))
	order := make([]node, 0, len(nodes))

	var dfs func(a node) error
	dfs = func(a node) error {
		if color[a] == visiting {
			return errors.New("cycle detected")
		}
		if color[a] == visited {
			return nil
		}
		color[a] = visiting

		for _, b := range a.incoming() {
			if err := dfs(b); err != nil {
				return err
			}
		}

		order = append(order, a)

		color[a] = visited
		return nil
	}
	for _, a := range nodes {
		if err := dfs(a); err != nil {
			return nil, err
		}
	}
	return order, nil
}
