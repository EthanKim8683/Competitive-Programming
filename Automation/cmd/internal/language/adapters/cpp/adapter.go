package cpp

import "github.com/EthanKim8683/Competitive-Programming/Automation/cmd/internal/language"

type CppAdapter struct {
	CppBundler
	CppCompiler
	CppExecutor
	CppMetadataExtractor
}

var _ language.Adapter = (*CppAdapter)(nil)

func NewCppAdapter() language.Adapter {
	return &CppAdapter{
		CppBundler:           CppBundler{},
		CppCompiler:          CppCompiler{},
		CppExecutor:          CppExecutor{},
		CppMetadataExtractor: CppMetadataExtractor{},
	}
}

var _ language.NewAdapterFunc = NewCppAdapter
