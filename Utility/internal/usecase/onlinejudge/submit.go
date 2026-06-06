package onlinejudge

import (
	"context"
	"fmt"
	neturl "net/url"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/domain"
	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/onlinejudge/codeforces"
	portonlinejudge "github.com/EthanKim8683/Competitive-Programming/Utility/internal/port/onlinejudge"
	"github.com/go-rod/rod"
)

func Submit(ctx context.Context, b *rod.Browser, url string, source string, opts ...portonlinejudge.SubmitOption) (domain.Submission, error) {
	cfg := portonlinejudge.SubmitConfig{}
	for _, opt := range opts {
		opt(&cfg)
	}

	u, err := neturl.Parse(url)
	if err != nil {
		return domain.Submission{}, err
	}

	if bundler := cfg.Bundler; bundler != nil {
		source, err = bundler.Bundle(source)
		if err != nil {
			return domain.Submission{}, fmt.Errorf("failed to bundle source: %w", err)
		}
	}

	host := u.Hostname()
	switch host {
	case "codeforces.com":
		return codeforces.Submit(ctx, b, url, source, cfg)
	default:
		return domain.Submission{}, fmt.Errorf("unsupported online judge: %s", host)
	}
}

var _ portonlinejudge.SubmitFunc = Submit
