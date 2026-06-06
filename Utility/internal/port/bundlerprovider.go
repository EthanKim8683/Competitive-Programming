package port

type BundlerProvider interface {
	Bundler() (Bundler, error)
}
