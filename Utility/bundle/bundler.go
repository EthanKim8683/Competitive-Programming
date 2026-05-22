package bundle

type Bundler interface {
	Bundle(path string) (string, error)
}
