package codeforces

import (
	"context"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/domain"
	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/port"
)

func (c *Codeforces) ScrapeContest(ctx context.Context, url string) (domain.Contest, error) {
	return domain.Contest{}, nil
}

var _ port.ContestScraper = (*Codeforces)(nil)
