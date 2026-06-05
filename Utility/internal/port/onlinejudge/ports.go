package portonlinejudge

import (
	"context"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/domain"
	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/port"
	"github.com/go-rod/rod"
)

type ScrapeContestFunc func(ctx context.Context, b *rod.Browser, url string) (domain.Contest, error)

type ScrapeProblemFunc func(ctx context.Context, b *rod.Browser, url string) (domain.Problem, error)

type SubmitConfig struct {
	Language domain.Language
	Bundler  port.Bundler
}

type SubmitOption func(config *SubmitConfig)

func WithLanguage(language domain.Language) SubmitOption {
	return func(config *SubmitConfig) {
		config.Language = language
	}
}

func WithBundler(bundler port.Bundler) SubmitOption {
	return func(config *SubmitConfig) {
		config.Bundler = bundler
	}
}

type SubmitFunc func(ctx context.Context, b *rod.Browser, url string, source string, opts ...SubmitOption) (domain.Submission, error)
