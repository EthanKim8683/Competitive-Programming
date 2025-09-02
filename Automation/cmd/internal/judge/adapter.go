package judge

type Adapter interface {
	Scraper
	Submitter
}

type NewAdapterFunc func() Adapter
