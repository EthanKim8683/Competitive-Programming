package codeforces

import (
	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/config"
	portonlinejudge "github.com/EthanKim8683/Competitive-Programming/Utility/internal/port/onlinejudge"
)

type Codeforces struct {
	cfg config.BrowserConfig
}

func New(cfg config.BrowserConfig) portonlinejudge.OnlineJudge {
	return &Codeforces{
		cfg: cfg,
	}
}
