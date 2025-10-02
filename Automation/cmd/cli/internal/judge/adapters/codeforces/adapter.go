package codeforces

import "github.com/EthanKim8683/Competitive-Programming/Automation/cmd/cli/internal/judge"

type CFAdapter struct {
	CFInitializer
	CFSubmitter
}

var _ judge.Adapter = (*CFAdapter)(nil)
