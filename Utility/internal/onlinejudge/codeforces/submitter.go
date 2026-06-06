package codeforces

import (
	"context"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/domain"
	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/port"
)

func (c *Codeforces) Submit(ctx context.Context, url string, solution domain.Solution) (domain.Submission, error) {
	return domain.Submission{}, nil
}

var _ port.Submitter = (*Codeforces)(nil)
