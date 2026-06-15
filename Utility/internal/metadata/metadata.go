package metadata

import (
	"fmt"
	"path/filepath"
	"strings"
)

type relPath string

func NewRelPath(path string) (relPath, error) {
	path = filepath.Clean(path)

	if filepath.IsAbs(path) {
		return "", fmt.Errorf("relative path is absolute: %s", path)
	}

	if strings.HasPrefix(path, "..") {
		return "", fmt.Errorf("relative path escapes root directory: %s", path)
	}

	if path == "." {
		return "", fmt.Errorf("relative path is root directory: %s", path)
	}

	return relPath(path), nil
}

type MetadataType string

const (
	MetadataTypeUnspecified MetadataType = ""
	MetadataTypeGXX         MetadataType = "g++"
)

type Metadata struct {
	RelPath relPath
	Type    MetadataType
	GXX     *GXXMetadata
}

func New(args []string) (*Metadata, error) {
	if len(args) == 0 {
		return nil, fmt.Errorf("no arguments provided: %v", args)
	}

	switch args[0] {
	case "g++":
		return gxxNew(args[1:])
	default:
		return nil, fmt.Errorf("unknown command: %s", args[0])
	}
}

func Join(lhs, rhs *Metadata) (*Metadata, error) {
	if lhs == nil {
		return rhs, nil
	}

	if lhs.RelPath != rhs.RelPath {
		return nil, fmt.Errorf("relative paths do not match: %s != %s", lhs.RelPath, rhs.RelPath)
	}

	switch lhs.Type {
	case MetadataTypeGXX:
		return gxxJoin(lhs, rhs)
	default:
		return nil, fmt.Errorf("unknown metadata type: %s", lhs.Type)
	}
}
