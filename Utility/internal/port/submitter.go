package port

import (
	"context"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/domain"
)

type Submitter interface {
	Submit(ctx context.Context, url string, solution domain.Solution) (domain.Submission, error)
}
