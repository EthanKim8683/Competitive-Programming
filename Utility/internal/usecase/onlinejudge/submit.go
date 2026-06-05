package onlinejudge

import (
	"context"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/domain"
	portonlinejudge "github.com/EthanKim8683/Competitive-Programming/Utility/internal/port/onlinejudge"
	"github.com/go-rod/rod"
)

func Submit(ctx context.Context, b *rod.Browser, url string, source string, opts ...portonlinejudge.SubmitOption) (domain.Submission, error) {
	return domain.Submission{}, nil
}

var _ portonlinejudge.SubmitFunc = Submit
