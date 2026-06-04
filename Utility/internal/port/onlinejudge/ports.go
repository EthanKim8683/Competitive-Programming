package portonlinejudge

import (
	"context"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/domain"
	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/port"
)

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

type OnlineJudge interface {
	ScrapeContest(ctx context.Context, url string) (domain.Contest, error)
	ScrapeProblem(ctx context.Context, url string) (domain.Problem, error)
	Submit(ctx context.Context, url string, source string, options ...SubmitOption) (domain.Submission, error)
}
