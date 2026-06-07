package gxx

import (
	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/generate"
	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/port"
)

func (g *GXX) GenerateMakefileRule(cfg generate.TargetConfig) (string, error) {
	return "", nil
}

var _ port.MakefileRuleGenerator = (*GXX)(nil)
