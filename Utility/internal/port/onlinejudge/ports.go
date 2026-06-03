package portonlinejudge

import (
	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/domain"
	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/port"
)

type ScrapeContest func(url string) (domain.Contest, error)

type ScrapeProblem func(url string) (domain.Problem, error)

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

type Submit func(url string, source string, options ...SubmitOption) (domain.Submission, error)

type OnlineJudge struct {
	ScrapeContest ScrapeContest
	ScrapeProblem ScrapeProblem
	Submit        Submit
}
