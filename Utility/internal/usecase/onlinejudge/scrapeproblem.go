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

func ScrapeProblem(ctx context.Context, b *rod.Browser, url string) (domain.Problem, error) {
	u, err := neturl.Parse(url)
	if err != nil {
		return domain.Problem{}, err
	}

	host := u.Hostname()
	switch host {
	case "codeforces.com":
		return codeforces.ScrapeProblem(ctx, b, url)
	default:
		return domain.Problem{}, fmt.Errorf("unsupported online judge: %s", host)
	}
}

var _ portonlinejudge.ScrapeProblemFunc = ScrapeProblem
