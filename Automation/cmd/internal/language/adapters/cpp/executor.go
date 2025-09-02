package cpp

import "github.com/EthanKim8683/Competitive-Programming/Automation/cmd/internal/language"

type CppExecutor struct{}

func (e *CppExecutor) Execute(executablePath string) (language.Execution, error) {
	return language.Execution{}, nil
}

var _ language.Executor = (*CppExecutor)(nil)
