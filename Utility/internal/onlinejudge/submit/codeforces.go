package submit

import (
	"context"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/domain"
	portonlinejudge "github.com/EthanKim8683/Competitive-Programming/Utility/internal/port/onlinejudge"
	"github.com/go-rod/rod"
)

func SubmitCodeforces(ctx context.Context, b *rod.Browser, url string, source string, opts ...portonlinejudge.SubmitOption) (domain.Submission, error) {
	return domain.Submission{}, nil
}

var _ portonlinejudge.SubmitFunc = SubmitCodeforces
