package codeforces

import (
	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/domain"
	portonlinejudge "github.com/EthanKim8683/Competitive-Programming/Utility/internal/port/onlinejudge"
)

func Submit(url string, source string, options ...portonlinejudge.SubmitOption) (domain.Submission, error) {
	config := portonlinejudge.SubmitConfig{}
	for _, option := range options {
		option(&config)
	}

	return domain.Submission{}, nil
}
