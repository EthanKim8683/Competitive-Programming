package codeforces

import "github.com/go-rod/rod"

type Codeforces struct {
	browser *rod.Browser
}

func NewCodeforces(b *rod.Browser) *Codeforces {
	return &Codeforces{
		browser: b,
	}
}
