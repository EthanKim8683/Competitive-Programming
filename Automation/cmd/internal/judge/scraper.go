package judge

type Scraper interface {
	Scrape(problemID string) (string, error)
}
