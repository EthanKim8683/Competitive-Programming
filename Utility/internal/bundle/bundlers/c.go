package bundlers

import (
	"errors"
	"fmt"
	"os"
	"path/filepath"
	"regexp"
	"slices"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/bundle"
	"go.uber.org/multierr"
)

var includeRegex = regexp.MustCompile(`[\t ]*#[\t ]*include[\t ]*"(.*?)"`)

type CBundler struct {
	includeDirs []string
}

func (b *CBundler) Bundle(path string) (string, error) {
	type node struct {
		name string
		path string

		content string
		headers []string

		adj []*node
	}
	headerNodes := make(map[string]*node)

	resolveIncludeDirs := func(path string) []string {
		return append([]string{filepath.Dir(path)}, b.includeDirs...)
	}

	resolveHeader := func(path string, header string) (string, error) {
		for _, includeDir := range resolveIncludeDirs(path) {
			headerPath := filepath.Join(includeDir, header)
			if _, err := os.Stat(headerPath); err == nil {
				return headerPath, nil
			}
		}
		return "", fmt.Errorf("could not resolve header: %s", header)
	}

	resolveNodeContent := func(n *node) error {
		data, err := os.ReadFile(n.path)
		if err != nil {
			return err
		}
		n.content = string(data)
		return nil
	}

	resolveNodeHeaders := func(n *node) {
		matches := includeRegex.FindAllStringSubmatch(n.content, -1)
		n.headers = make([]string, 0, len(matches))
		for _, match := range matches {
			n.headers = append(n.headers, match[1])
		}
	}

	var resolveNode func(*node) error
	resolveNode = func(a *node) error {
		if err := resolveNodeContent(a); err != nil {
			return err
		}
		resolveNodeHeaders(a)

		var errs error
		for _, header := range a.headers {
			headerPath, err := resolveHeader(a.path, header)

			b, ok := headerNodes[headerPath]
			if !ok {
				if err != nil {
					errs = multierr.Append(errs, err)
					continue
				}

				b = &node{
					name: header,
					path: headerPath,
				}
				headerNodes[headerPath] = b

				err = resolveNode(b)
				if err != nil {
					errs = multierr.Append(errs, err)
					continue
				}
			}

			b.adj = append(b.adj, a)
		}
		return errs
	}

	r := &node{
		name: "main",
		path: path,
	}
	if err := resolveNode(r); err != nil {
		return "", err
	}

	seen := make(map[*node]bool, 1+len(headerNodes))
	order := make([]*node, 0, 1+len(headerNodes))
	var toposort func(*node)
	toposort = func(a *node) {
		if seen[a] {
			return
		}
		seen[a] = true
		for _, b := range a.adj {
			toposort(b)
		}
		order = append(order, a)
	}
	toposort(r)
	for _, a := range headerNodes {
		toposort(a)
	}
	slices.Reverse(order)

	for n := range seen {
		delete(seen, n)
	}
	for _, a := range order {
		for _, b := range a.adj {
			if seen[b] {
				return "", errors.New("found cyclic dependency")
			}
		}
		seen[a] = true
	}

	bundled := ""
	for _, a := range order {
		bundled += includeRegex.ReplaceAllString(a.content, "// $0")
		bundled += "\n"
	}
	return bundled, nil
}

var _ bundle.Bundler = (*CBundler)(nil)

func NewCBundler(includeDirs []string) bundle.Bundler {
	return &CBundler{
		includeDirs: includeDirs,
	}
}
