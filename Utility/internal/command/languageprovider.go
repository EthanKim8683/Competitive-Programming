package command

import (
	"fmt"
	"path/filepath"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/domain"
	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/port"
	"github.com/spf13/cobra"
	"go.uber.org/multierr"
)

const (
	languageFlagName      = "language"
	languageFlagShortname = "l"
	languageFlagValue     = "cpp23"
)

var languageMap = map[domain.Language]struct{}{
	domain.LanguageCpp17: {},
	domain.LanguageCpp20: {},
	domain.LanguageCpp23: {},
}

type LanguageProvider struct {
	command *cobra.Command

	FilePath *string

	LanguageFlagUsage string
	LanguageVar       string
}

func (l *LanguageProvider) Bind(command *cobra.Command) {
	l.command = command

	command.Flags().StringVarP(
		&l.LanguageVar,
		languageFlagName,
		languageFlagShortname,
		languageFlagValue,
		l.LanguageFlagUsage,
	)
}

func (l *LanguageProvider) resolveUsingLanguageFlag() (domain.Language, error) {
	if !l.command.Flags().Changed(languageFlagName) {
		return domain.LanguageUnspecified, fmt.Errorf("language flag is not set")
	}

	language := domain.Language(l.LanguageVar)
	if _, ok := languageMap[language]; !ok {
		return domain.LanguageUnspecified, fmt.Errorf("unknown language: %s", language)
	}
	return language, nil
}

func (l *LanguageProvider) resolveUsingFilePath() (domain.Language, error) {
	if l.FilePath == nil {
		return domain.LanguageUnspecified, fmt.Errorf("file path is not set")
	}

	filePath := *l.FilePath
	ext := filepath.Ext(filePath)
	switch ext {
	case ".cpp":
		return domain.LanguageCpp23, nil
	case ".py":
		return domain.LanguagePython3, nil
	default:
		return domain.LanguageUnspecified, fmt.Errorf("could not infer language from file extension: %s", filePath)
	}
}

func (l *LanguageProvider) Language() (domain.Language, error) {
	var errs error

	if language, err := l.resolveUsingLanguageFlag(); err == nil {
		return language, nil
	} else {
		errs = multierr.Append(errs, err)
	}

	if language, err := l.resolveUsingFilePath(); err == nil {
		return language, nil
	} else {
		errs = multierr.Append(errs, err)
	}

	return domain.LanguageUnspecified, errs
}

var _ port.LanguageProvider = (*LanguageProvider)(nil)
