package automation

import (
	automationv1 "github.com/EthanKim8683/Competitive-Programming/Utility/gen/automation/v1"
)

func ScrapeProblem(url string) error {
	response := &automationv1.ScrapeProblemResponse{}
	if err := rpc(
		"automation.v1.scrape_problem",
		&automationv1.ScrapeProblemRequest{
			Url: url,
		},
		response,
	); err != nil {
		return err
	}
	return nil
}
