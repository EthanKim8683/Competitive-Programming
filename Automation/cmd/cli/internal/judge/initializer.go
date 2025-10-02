package judge

type Initializer interface {
	Initialize(id string) (string, error)
}
