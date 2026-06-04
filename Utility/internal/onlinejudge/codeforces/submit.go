package codeforces

import (
	"context"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/domain"
	portonlinejudge "github.com/EthanKim8683/Competitive-Programming/Utility/internal/port/onlinejudge"
)

func (oj *Codeforces) Submit(ctx context.Context, url string, source string, opts ...portonlinejudge.SubmitOption) (domain.Submission, error) {
	config := portonlinejudge.SubmitConfig{}
	for _, opt := range opts {
		opt(&config)
	}

	return domain.Submission{}, nil
}
