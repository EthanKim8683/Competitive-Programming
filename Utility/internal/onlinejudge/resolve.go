package onlinejudge

import (
	"fmt"
	neturl "net/url"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/onlinejudge/atcoder"
	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/onlinejudge/codeforces"
	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/onlinejudge/vjudge"
	portonlinejudge "github.com/EthanKim8683/Competitive-Programming/Utility/internal/port/onlinejudge"
)

func Resolve(url string) (*portonlinejudge.OnlineJudge, error) {
	u, err := neturl.Parse(url)
	if err != nil {
		return nil, err
	}
	host := u.Hostname()
	switch host {
	case "atcoder.jp":
		return &atcoder.OnlineJudge, nil
	case "codeforces.com":
		return &codeforces.OnlineJudge, nil
	case "vjudge.net":
		return &vjudge.OnlineJudge, nil
	default:
		return nil, fmt.Errorf("unknown host: %s", host)
	}
}
