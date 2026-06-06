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

func ScrapeContest(ctx context.Context, b *rod.Browser, url string) (domain.Contest, error) {
	u, err := neturl.Parse(url)
	if err != nil {
		return domain.Contest{}, err
	}

	host := u.Hostname()
	switch host {
	case "codeforces.com":
		return codeforces.ScrapeContest(ctx, b, url)
	default:
		return domain.Contest{}, fmt.Errorf("unsupported online judge: %s", host)
	}
}

var _ portonlinejudge.ScrapeContestFunc = ScrapeContest
