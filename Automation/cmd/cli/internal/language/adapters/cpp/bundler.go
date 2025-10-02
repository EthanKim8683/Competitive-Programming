package cpp

import "github.com/EthanKim8683/Competitive-Programming/Automation/cmd/cli/internal/language"

type CppBundler struct{}

func (b *CppBundler) Bundle(contents string) (string, error) {
	return "", nil
}

var _ language.Bundler = (*CppBundler)(nil)
