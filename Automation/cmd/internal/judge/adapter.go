package judge

type Adapter interface {
	Initializer
	Submitter
}

type NewAdapterFunc func() Adapter
