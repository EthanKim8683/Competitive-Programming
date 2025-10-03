package cpp

import "github.com/EthanKim8683/Competitive-Programming/Automation/internal/language"

type CppAdapter struct {
	CppBundler
	CppInitializer
}

var _ language.Adapter = (*CppAdapter)(nil)

func NewCppAdapter() language.Adapter {
	return &CppAdapter{
		CppBundler:     CppBundler{},
		CppInitializer: CppInitializer{},
	}
}

var _ language.NewAdapterFunc = NewCppAdapter
