package codeforces

import (
	"context"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/domain"
	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/port"
)

func (c *Codeforces) ScrapeProblem(ctx context.Context, url string) (domain.Problem, error) {
	return domain.Problem{}, nil
}

var _ port.ProblemScraper = (*Codeforces)(nil)
