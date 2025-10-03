package language

type Adapter interface {
	Bundler
	Initializer
}

type NewAdapterFunc func() Adapter
