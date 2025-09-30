package cpp

import "github.com/EthanKim8683/Competitive-Programming/Automation/cmd/internal/language"

type CppInitializer struct {
}

func (b *CppInitializer) Initialize() error {
	return nil
}

var _ language.Initializer = (*CppInitializer)(nil)
