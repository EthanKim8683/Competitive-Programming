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

var cIncludeRegexp = regexp.MustCompile(`(?m)^\s*#\s*include\s*"((?:[^"]|\")+)"`)

type cBundler struct {
	includePaths []string
}

func (b *cBundler) commentIncludes(source string) string {
	return cIncludeRegexp.ReplaceAllString(source, "// $0")
}

func (b *cBundler) extractIncludes(source string) []string {
	matches := cIncludeRegexp.FindAllStringSubmatch(source, -1)
	includes := make([]string, 0, len(matches))
	for _, match := range matches {
		includes = append(includes, match[1])
	}
	return includes
}

func (b *cBundler) resolveInclude(include, from string) (absPath string, err error) {
	if filepath.IsAbs(include) {
		return include, nil
	}

	absPath = filepath.Join(filepath.Dir(from), include)
	if _, err := os.Stat(absPath); err == nil {
		return absPath, nil
	}

	for _, path := range b.includePaths {
		absPath = filepath.Join(path, include)
		if _, err := os.Stat(absPath); err == nil {
			return absPath, nil
		}
	}

	return "", fmt.Errorf("could not resolve include: %s", include)
}

func (b *cBundler) resolveIncludes(includes []string, from string) ([]string, error) {
	var errs error

	deps := make([]string, 0, len(includes))
	for _, include := range includes {
		dep, err := b.resolveInclude(include, from)
		if err != nil {
			errs = errors.Join(errs, err)
			continue
		}

		deps = append(deps, dep)
	}

	if errs != nil {
		return nil, errs
	}
	return deps, nil
}

func (b *cBundler) resolve(absPath string) (string, []string, error) {
	data, err := os.ReadFile(absPath)
	if err != nil {
		return "", nil, err
	}
	source := string(data)

	deps, err := b.resolveIncludes(b.extractIncludes(source), absPath)
	if err != nil {
		return "", nil, err
	}

	return b.commentIncludes(source), deps, nil
}

func (b *cBundler) Bundle(absPath string) (string, error) {
	if !filepath.IsAbs(absPath) {
		return "", fmt.Errorf("source path is not absolute: %s", absPath)
	}

	var errs error
	var sb strings.Builder

	type visitState int
	const (
		unvisited visitState = iota
		visiting
		visited
	)

	state := make(map[string]visitState)
	var dfs func(absPath string)
	dfs = func(absPath string) {
		absPath = filepath.Clean(absPath)

		switch state[absPath] {
		case unvisited:
			state[absPath] = visiting
		case visiting:
			errs = errors.Join(errs, errors.New("cycle detected"))
			return
		case visited:
			return
		}
		defer func() {
			state[absPath] = visited
		}()

		fragment, deps, err := b.resolve(absPath)
		if err != nil {
			errs = errors.Join(errs, err)
			return
		}

		for _, dep := range deps {
			dfs(dep)
		}

		sb.WriteString(strings.TrimSpace(fragment))
		sb.WriteString("\n\n")
	}
	dfs(absPath)

	if errs != nil {
		return "", fmt.Errorf("failed to bundle: %w", errs)
	}
	return sb.String(), nil
}

var _ port.Bundler = (*cBundler)(nil)

func NewC(includePaths []string) port.Bundler {
	return &cBundler{
		includePaths: includePaths,
	}
}
