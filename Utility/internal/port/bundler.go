package port

type Bundler interface {
	Bundle(source string) (string, error)
}
