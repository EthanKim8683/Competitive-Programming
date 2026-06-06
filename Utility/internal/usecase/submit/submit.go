package submit

import (
	"context"
	"fmt"
	neturl "net/url"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/domain"
	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/onlinejudge/codeforces"
	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/port"
	"github.com/go-rod/rod"
)

type Submit struct {
	browser *rod.Browser
}

func (s *Submit) Execute(ctx context.Context, url string, solution domain.Solution) (domain.Submission, error) {
	u, err := neturl.Parse(url)
	if err != nil {
		return domain.Submission{}, err
	}

	var submitter port.Submitter
	switch u.Host {
	case "codeforces.com":
		submitter = codeforces.New(s.browser)
	default:
		return domain.Submission{}, fmt.Errorf("unknown online judge: %s", url)
	}

	return submitter.Submit(ctx, url, solution)
}
