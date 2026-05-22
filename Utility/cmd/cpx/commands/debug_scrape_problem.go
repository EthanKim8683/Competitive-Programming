package commands

import (
	"github.com/EthanKim8683/Competitive-Programming/Utility/automation"
	"github.com/spf13/cobra"
)

var debugScrapeProblemCmd = &cobra.Command{
	Use:   "scrape-problem <url>",
	Short: "Scrape a problem",
	Long:  "Scrape a problem and output the inputs to standard output",
	Args:  cobra.ExactArgs(1),
	Run: func(cmd *cobra.Command, args []string) {
		url := args[0]
		automation.ScrapeProblem(url)
	},
}

func init() {
	RootCmd.AddCommand(debugScrapeProblemCmd)
}
