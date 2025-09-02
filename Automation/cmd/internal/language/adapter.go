package language

type Adapter interface {
	Bundler
	Compiler
	Executor
	MetadataExtractor
}

type NewAdapterFunc func() Adapter
