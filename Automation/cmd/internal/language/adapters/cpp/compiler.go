package cpp

import (
	"github.com/EthanKim8683/Competitive-Programming/Automation/cmd/internal/language"
)

type CppCompiler struct{}

func (c *CppCompiler) Compile(contents string, options map[string]string) (string, error) {
	return "", nil
}

var _ language.Compiler = (*CppCompiler)(nil)
