package commands

import (
	"github.com/EthanKim8683/Competitive-Programming/Utility/automation"
	"github.com/spf13/cobra"
)

var debugScrapeContestCmd = &cobra.Command{
	Use:   "scrape-contest <url>",
	Short: "Scrape a contest",
	Long:  "Scrape a contest and output the problems to standard output",
	Args:  cobra.ExactArgs(1),
	Run: func(cmd *cobra.Command, args []string) {
		url := args[0]
		automation.ScrapeContest(url)
	},
}

func init() {
	RootCmd.AddCommand(debugScrapeContestCmd)
}
