package cpp

import "github.com/EthanKim8683/Competitive-Programming/Automation/cmd/internal/language"

type CppMetadataExtractor struct{}

func (m *CppMetadataExtractor) ExtractMetadata(contents string) (string, error) {
	return "", nil
}

var _ language.MetadataExtractor = (*CppMetadataExtractor)(nil)
