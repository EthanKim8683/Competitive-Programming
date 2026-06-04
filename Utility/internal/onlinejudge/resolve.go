package onlinejudge

import (
	"fmt"
	neturl "net/url"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/onlinejudge/codeforces"
	portonlinejudge "github.com/EthanKim8683/Competitive-Programming/Utility/internal/port/onlinejudge"
)

func Resolve(url string) (*portonlinejudge.OnlineJudge, error) {
	u, err := neturl.Parse(url)
	if err != nil {
		return nil, err
	}
	host := u.Hostname()
	switch host {
	case "codeforces.com":
		return codeforces.New(cfg), nil
	default:
		return nil, fmt.Errorf("unknown host: %s", host)
	}
}
