package codeforces

import (
	"errors"
	"path/filepath"
	"testing"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/domain"
	"github.com/stretchr/testify/assert"
	"github.com/stretchr/testify/require"
)

func TestParseProblemType(t *testing.T) {
	t.Parallel()

	tests := map[string]struct {
		path        string
		problemType domain.ProblemType
		err         error
	}{
		"stdiobatch": {
			path:        "stdiobatch.html",
			problemType: domain.ProblemTypeStdioBatch,
		},
		"stdiointeractive": {
			path:        "stdiointeractive.html",
			problemType: domain.ProblemTypeStdioInteractive,
		},
		"stdioruntwice": {
			path:        "stdioruntwice.html",
			problemType: domain.ProblemTypeStdioRunTwice,
		},
		"error": {
			path: "bogus.html",
			err:  errors.New("could not determine problem type"),
		},
	}
	for name, test := range tests {
		t.Run(name, func(t *testing.T) {
			t.Parallel()

			d := readDocument(t, filepath.Join("problemscraper", test.path))
			problemType, err := parseProblemType(d)
			if test.err != nil {
				require.EqualError(t, err, test.err.Error())
				assert.Empty(t, problemType)
			} else {
				require.NoError(t, err)
				assert.Equal(t, test.problemType, problemType)
			}
		})
	}
}

func TestParseStdioBatch(t *testing.T) {
	t.Parallel()

	expectedBatch := &domain.StdioBatch{
		Inputs: []string{
			`3
2
5
7`,
		},
		Outputs: []string{
			`2 2
1 4 4 6 6
4 4 6 6 9 9 4`,
		},
	}

	d := readDocument(t, filepath.Join("problemscraper", "stdiobatch.html"))
	batch := parseStdioBatch(d)
	assert.Equal(t, expectedBatch, batch)
}
