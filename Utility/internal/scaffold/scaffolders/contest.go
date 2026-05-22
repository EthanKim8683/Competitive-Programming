package scaffolders

import "github.com/EthanKim8683/Competitive-Programming/Utility/internal/scaffold"

type ContestScaffolder struct {
}

func (i *ContestScaffolder) Scaffold(path string) error {
	return nil
}

var _ scaffold.Scaffolder = (*ContestScaffolder)(nil)

func NewContestScaffolder() scaffold.Scaffolder {
	return &ContestScaffolder{}
}
