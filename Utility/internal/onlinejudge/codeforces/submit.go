package codeforces

import (
	"context"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/browser/client"
	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/domain"
	portonlinejudge "github.com/EthanKim8683/Competitive-Programming/Utility/internal/port/onlinejudge"
	"github.com/go-rod/rod"
)

func (oj *Codeforces) Submit(ctx context.Context, url string, source string, opts ...portonlinejudge.SubmitOption) (domain.Submission, error) {
	config := portonlinejudge.SubmitConfig{}
	for _, opt := range opts {
		opt(&config)
	}

	var c *client.Client

	h, err := c.Acquire(
		client.WithContext(ctx),
	)
	if err != nil {
		return domain.Submission{}, err
	}
	defer h.Release()

	b := rod.New().ControlURL(h.ControlURL())

	b.Get(url)

	return domain.Submission{}, nil
}
