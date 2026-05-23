package commands

import (
	"fmt"
	"os"

	"github.com/EthanKim8683/Competitive-Programming/Utility/automation"
	scrapecontestv1 "github.com/EthanKim8683/Competitive-Programming/Utility/gen/automation/scrape_contest/v1"
	"github.com/spf13/cobra"
)

var debugScrapeContestCmd = &cobra.Command{
	Use:   "scrape-contest <url>",
	Short: "Scrape a contest",
	Long:  "Scrape a contest and output the problems to standard output",
	Args:  cobra.ExactArgs(1),
	Run: func(cmd *cobra.Command, args []string) {
		url := args[0]

		request := &scrapecontestv1.ScrapeContestRequest{
			Url: url,
		}
		response := &scrapecontestv1.ScrapeContestResponse{}
		if err := automation.ScrapeContest(request, response); err != nil {
			fmt.Fprintln(os.Stderr, err)
			os.Exit(1)
		}
		fmt.Println(response.Contest)
	},
}

func init() {
	RootCmd.AddCommand(debugScrapeContestCmd)
}
