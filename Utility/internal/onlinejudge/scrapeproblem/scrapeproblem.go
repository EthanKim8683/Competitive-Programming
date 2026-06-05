package scrapeproblem

import (
	"context"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/domain"
	portonlinejudge "github.com/EthanKim8683/Competitive-Programming/Utility/internal/port/onlinejudge"
	"github.com/go-rod/rod"
)

func ScrapeProblem(ctx context.Context, b *rod.Browser, url string) (domain.Problem, error) {
	return domain.Problem{}, nil
}

var _ portonlinejudge.ScrapeProblemFunc = ScrapeProblem
