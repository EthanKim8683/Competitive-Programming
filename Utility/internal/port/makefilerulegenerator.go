package port

import "github.com/EthanKim8683/Competitive-Programming/Utility/internal/generate"

type MakefileRuleGenerator interface {
	GenerateMakefileRule(cfg generate.TargetConfig) (string, error)
}
