package automation

import (
	scrapecontestv1 "github.com/EthanKim8683/Competitive-Programming/Utility/gen/automation/scrape_contest/v1"
	scrapeproblemv1 "github.com/EthanKim8683/Competitive-Programming/Utility/gen/automation/scrape_problem/v1"
	submitv1 "github.com/EthanKim8683/Competitive-Programming/Utility/gen/automation/submit/v1"
	"github.com/nats-io/nats.go"
	"google.golang.org/protobuf/proto"
)

func createRpc[T proto.Message, R proto.Message](subject string) func(request T, response R) error {
	return func(request T, response R) error {
		nc, err := nats.Connect("nats://127.0.0.1:4222")
		if err != nil {
			return err
		}
		defer nc.Close()

		data, err := proto.Marshal(request)
		if err != nil {
			return err
		}

		msg, err := nc.Request(subject, data, nats.DefaultTimeout)
		if err != nil {
			return err
		}

		if err := proto.Unmarshal(msg.Data, response); err != nil {
			return err
		}

		return nil
	}
}

var (
	ScrapeContest = createRpc[
		*scrapecontestv1.ScrapeContestRequest,
		*scrapecontestv1.ScrapeContestResponse,
	]("automation.v1.scrape_contest")

	ScrapeProblem = createRpc[
		*scrapeproblemv1.ScrapeProblemRequest,
		*scrapeproblemv1.ScrapeProblemResponse,
	]("automation.v1.scrape_problem")

	Submit = createRpc[
		*submitv1.SubmitRequest,
		*submitv1.SubmitResponse,
	]("automation.v1.submit")
)
