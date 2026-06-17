package codeforces_test

import (
	"context"
	"testing"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/domain"
	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/onlinejudge/codeforces"
	"github.com/go-rod/rod"
	"github.com/go-rod/rod/lib/launcher"
	"github.com/stretchr/testify/assert"
	"github.com/stretchr/testify/require"
)

func TestProblemScraper(t *testing.T) {
	t.Parallel()

	u := launcher.NewUserMode().
		UserDataDir(t.TempDir()).
		Headless(false).
		MustLaunch()

	b := rod.New().
		ControlURL(u).
		MustConnect()

	cf := codeforces.New(b)

	var tests = map[string]struct {
		url      string
		expected domain.Problem
	}{
		"batch": {
			url: "https://codeforces.com/contest/2158/problem/F1",
			expected: domain.Problem{
				URL:  "https://codeforces.com/contest/2158/problem/F1",
				Type: domain.ProblemTypeBatch,
				Batch: &domain.BatchProblem{
					Inputs: []string{`3
2
5
7`},
					Outputs: []string{`2 2
1 4 4 6 6
4 4 6 6 9 9 4`},
				},
			},
		},
		"interactive": {
			url: "https://codeforces.com/problemset/problem/2196/C2",
			expected: domain.Problem{
				URL:         "https://codeforces.com/problemset/problem/2196/C2",
				Type:        domain.ProblemTypeInteractive,
				Interactive: &domain.InteractiveProblem{},
			},
		},
		"communication": {
			url: "https://codeforces.com/problemset/problem/2168/B",
			expected: domain.Problem{
				URL:           "https://codeforces.com/problemset/problem/2168/B",
				Type:          domain.ProblemTypeCommunication,
				Communication: &domain.CommunicationProblem{},
			},
		},
	}
	for name, test := range tests {
		t.Run(name, func(t *testing.T) {
			problem, err := cf.ScrapeProblem(context.Background(), test.url)
			require.NoError(t, err)

			assert.Equal(t, test.expected, problem)
		})
	}
}
