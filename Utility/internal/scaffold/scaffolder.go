package scaffold

type Scaffolder interface {
	Scaffold(path string) error
}
