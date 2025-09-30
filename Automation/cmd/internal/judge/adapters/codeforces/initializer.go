package codeforces

import "github.com/EthanKim8683/Competitive-Programming/Automation/cmd/internal/judge"

type CFInitializer struct {
}

func (*CFInitializer) Initialize(problemID string) (string, error) {
	return "", nil
}

var _ judge.Initializer = (*CFInitializer)(nil)
