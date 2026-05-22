package automation

import (
	automationv1 "github.com/EthanKim8683/Competitive-Programming/Utility/gen/automation/v1"
)

func ScrapeContest(url string) error {
	response := &automationv1.ScrapeContestResponse{}
	if err := rpc(
		"automation.v1.scrape_contest",
		&automationv1.ScrapeContestRequest{
			Url: url,
		},
		response,
	); err != nil {
		return err
	}
	return nil
}
