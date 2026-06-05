package scrapecontest

import (
	"context"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/domain"
	portonlinejudge "github.com/EthanKim8683/Competitive-Programming/Utility/internal/port/onlinejudge"
	"github.com/go-rod/rod"
)

func ScrapeCodeforcesContest(ctx context.Context, b *rod.Browser, url string) (domain.Contest, error) {
	return domain.Contest{}, nil
}

var _ portonlinejudge.ScrapeContestFunc = ScrapeCodeforcesContest
