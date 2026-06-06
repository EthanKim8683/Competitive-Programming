package port

import (
	"context"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/domain"
)

type ProblemScraper interface {
	ScrapeProblem(ctx context.Context, url string) (domain.Problem, error)
}
