package bundler

import (
	"errors"
	"fmt"
	"os"
	"path/filepath"
	"regexp"
	"strings"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/port"
)

var cIncludeRegex = regexp.MustCompile(`(?m)^\s*#\s*include\s*"((?:[^"]|\")+)"`)

type cBundler struct {
	includePaths []string
}

type cNode struct {
	*cState
	absPath string

	commented    string
	dependencies []*cNode
}

func (n *cNode) extractIncludes(source string) []string {
	matches := cIncludeRegex.FindAllStringSubmatch(source, -1)
	includes := make([]string, 0, len(matches))
	for _, match := range matches {
		includes = append(includes, match[1])
	}
	return includes
}

func (n *cNode) commentIncludes(source string) string {
	return cIncludeRegex.ReplaceAllString(source, "// $0")
}

func (n *cNode) resolveInclude(include string) (string, error) {
	if filepath.IsAbs(include) {
		absPath := include
		if _, err := os.Stat(absPath); err != nil {
			return "", fmt.Errorf("could not stat include: %w", err)
		}
		return absPath, nil
	}

	absPath := filepath.Join(filepath.Dir(n.absPath), include)
	if _, err := os.Stat(absPath); err == nil {
		return absPath, nil
	}

	for _, includePath := range n.includePaths {
		absPath := filepath.Join(includePath, include)
		if _, err := os.Stat(absPath); err == nil {
			return absPath, nil
		}
	}

	return "", fmt.Errorf("could not resolve include: %s", include)
}

func (n *cNode) process() ([]*cNode, error) {
	data, err := os.ReadFile(n.absPath)
	if err != nil {
		return nil, fmt.Errorf("could not read source: %w", err)
	}
	source := string(data)

	includes := n.extractIncludes(source)
	commented := n.commentIncludes(source)

	var errs error
	dependencies := make([]*cNode, 0, len(includes))
	for _, include := range includes {
		absPath, err := n.resolveInclude(include)
		if err != nil {
			errs = errors.Join(errs, err)
			continue
		}

		dependency := n.resolveNode(absPath)
		dependencies = append(dependencies, dependency)
	}
	if errs != nil {
		return nil, fmt.Errorf("could not process %s: %w", n.absPath, errs)
	}

	n.commented = commented
	n.dependencies = dependencies

	return dependencies, nil
}

func (n *cNode) incoming() []node {
	incoming := make([]node, 0, len(n.dependencies))
	for _, dependency := range n.dependencies {
		incoming = append(incoming, dependency)
	}
	return incoming
}

var _ node = (*cNode)(nil)

type cState struct {
	includePaths []string

	node map[string]*cNode
}

func (s *cState) resolveNode(absPath string) *cNode {
	absPath = filepath.Clean(absPath)

	if n, ok := s.node[absPath]; ok {
		return n
	}

	n := &cNode{
		cState:  s,
		absPath: absPath,
	}

	s.node[absPath] = n

	return n
}

func newCState(includePaths []string) *cState {
	return &cState{
		includePaths: includePaths,
		node:         make(map[string]*cNode),
	}
}

func (b *cBundler) Bundle(sourcePath string) (string, error) {
	if !filepath.IsAbs(sourcePath) {
		return "", fmt.Errorf("source path is not absolute: %s", sourcePath)
	}

	s := newCState(b.includePaths)

	visited := make(map[*cNode]struct{})
	var errs error
	var nodes []node
	var dfs func(a *cNode)
	dfs = func(a *cNode) {
		if _, ok := visited[a]; ok {
			return
		}
		visited[a] = struct{}{}

		nodes = append(nodes, a)

		dependencies, err := a.process()
		if err != nil {
			errs = errors.Join(errs, err)
			return
		}

		for _, dependency := range dependencies {
			dfs(dependency)
		}
	}
	dfs(s.resolveNode(sourcePath))
	if errs != nil {
		return "", fmt.Errorf("could not resolve dependency graph: %w", errs)
	}

	order, err := toposort(nodes)
	if err != nil {
		return "", fmt.Errorf("could not flatten dependency graph: %w", err)
	}

	var sb strings.Builder
	for _, node := range order {
		sb.WriteString(strings.TrimSpace(node.(*cNode).commented))
		sb.WriteString("\n\n")
	}
	return sb.String(), nil
}

var _ port.Bundler = &cBundler{}

func NewCBundler(includePaths []string) port.Bundler {
	return &cBundler{
		includePaths: includePaths,
	}
}
