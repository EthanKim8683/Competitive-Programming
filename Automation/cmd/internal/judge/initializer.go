package judge

type Initializer interface {
	Initialize(problemID string) (string, error)
}
