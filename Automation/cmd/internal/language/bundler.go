package language

type Bundler interface {
	Bundle(contents string) (string, error)
}
