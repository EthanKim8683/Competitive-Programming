package command

import (
	"fmt"

	cbundler "github.com/EthanKim8683/Competitive-Programming/Utility/internal/bundler/c"
	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/domain"
	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/port"
	"github.com/spf13/cobra"
)

type BundlerProvider struct {
	LanguageProvider port.LanguageProvider

	cbundlerIncludeDirs []string
}

func (b *BundlerProvider) Bind(command *cobra.Command) {
	command.Flags().StringSliceVar(&b.cbundlerIncludeDirs, "c_include", []string{}, "cbundler: include paths")
}

func (b *BundlerProvider) Bundler() (port.Bundler, error) {
	language, err := b.LanguageProvider.Language()
	if err != nil {
		return nil, err
	}

	switch language {
	case domain.LanguageCpp17, domain.LanguageCpp20, domain.LanguageCpp23:
		return cbundler.New(b.cbundlerIncludeDirs), nil
	case domain.LanguageUnspecified:
		return nil, nil
	default:
		return nil, fmt.Errorf("unsupported language: %s", language)
	}
}

var _ port.BundlerProvider = (*BundlerProvider)(nil)
