package metadata

import (
	"errors"
	"fmt"
	"strings"
)

type gxxStandard string

const (
	GXXStandardUnspecified gxxStandard = ""
	GXXStandardCXX17       gxxStandard = "c++17"
	GXXStandardCXX20       gxxStandard = "c++20"
	GXXStandardCXX23       gxxStandard = "c++23"
)

func NewGXXStandard(standard string) (gxxStandard, error) {
	switch standard {
	case "", "c++17", "c++20", "c++23":
		return gxxStandard(standard), nil
	default:
		return "", fmt.Errorf("unknown standard: %s", standard)
	}
}

type GXXMetadata struct {
	Standard     gxxStandard
	IncludePaths []string
}

type gxxMetadataBuilder struct {
	errs         error
	sourcePaths  []relPath
	standards    []gxxStandard
	includePaths []string
}

func (b *gxxMetadataBuilder) addErr(err error) {
	b.errs = errors.Join(b.errs, err)
}

func (b *gxxMetadataBuilder) addSourcePath(arg string) {
	sourcePath, err := NewRelPath(arg)
	if err != nil {
		b.addErr(err)
		return
	}
	b.sourcePaths = append(b.sourcePaths, sourcePath)
}

func (b *gxxMetadataBuilder) addStandard(arg string) {
	standard, err := NewGXXStandard(arg)
	if err != nil {
		b.addErr(err)
		return
	}
	b.standards = append(b.standards, standard)
}

func (b *gxxMetadataBuilder) addIncludePath(arg string) {
	b.includePaths = append(b.includePaths, arg)
}

func (b *gxxMetadataBuilder) build() (*Metadata, error) {
	var sourcePath relPath
	switch {
	case len(b.sourcePaths) == 0:
		b.addErr(errors.New("no source files specified"))
	case len(b.sourcePaths) > 1:
		b.addErr(fmt.Errorf("multiple source files specified: %v", b.sourcePaths))
	default:
		sourcePath = b.sourcePaths[0]
	}

	var standard gxxStandard
	switch {
	case len(b.standards) > 1:
		b.addErr(fmt.Errorf("multiple standards specified: %v", b.standards))
	case len(b.standards) == 1:
		standard = b.standards[0]
	}

	if b.errs != nil {
		return nil, b.errs
	}

	return &Metadata{
		RelPath: sourcePath,
		Type:    MetadataTypeGXX,
		GXX: &GXXMetadata{
			Standard:     standard,
			IncludePaths: b.includePaths,
		},
	}, nil
}

func gxxNew(args []string) (*Metadata, error) {
	var errs error
	var b gxxMetadataBuilder

	i := 0
	eatArg := func() (string, bool) {
		if i >= len(args) {
			return "", false
		}

		arg := args[i]
		i++

		return arg, true
	}

	for {
		arg, ok := eatArg()
		if !ok {
			break
		}

		if strings.HasPrefix(arg, "-") {
			switch {
			case arg == "-o":
				_, ok := eatArg()
				if !ok {
					errs = errors.Join(errs, errors.New("no output file specified"))
					break
				}
			case arg == "-std":
				standardArg, ok := eatArg()
				if !ok {
					errs = errors.Join(errs, errors.New("no standard specified"))
					break
				}
				b.addStandard(standardArg)
			case arg == "-I":
				includePathArg, ok := eatArg()
				if !ok {
					errs = errors.Join(errs, errors.New("no include path specified"))
					break
				}
				b.addIncludePath(includePathArg)
			case strings.HasPrefix(arg, "-std="):
				b.addStandard(strings.TrimPrefix(arg, "-std="))
			case strings.HasPrefix(arg, "-I"):
				b.addIncludePath(strings.TrimPrefix(arg, "-I"))
			}
		} else {
			b.addSourcePath(arg)
		}
	}

	m, err := b.build()
	if err != nil {
		errs = errors.Join(errs, fmt.Errorf("failed to build metadata: %w", err))
	}

	if errs != nil {
		return nil, errs
	}

	return m, nil
}

func gxxJoin(lhs, rhs *Metadata) (*Metadata, error) {
	if lhs.RelPath != rhs.RelPath {
		return nil, fmt.Errorf("rel paths do not match: %s != %s", lhs.RelPath, rhs.RelPath)
	}

	return rhs, nil
}
