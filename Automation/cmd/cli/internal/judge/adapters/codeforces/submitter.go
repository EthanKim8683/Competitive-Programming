package codeforces

import "github.com/EthanKim8683/Competitive-Programming/Automation/cmd/cli/internal/judge"

type CFSubmitter struct {
}

func (s *CFSubmitter) Submit(problemID string, codePath string) (string, error) {
	return "", nil
}

var _ judge.Submitter = (*CFSubmitter)(nil)
