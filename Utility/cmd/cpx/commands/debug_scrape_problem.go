package commands

import (
	"fmt"
	"os"

	"github.com/EthanKim8683/Competitive-Programming/Utility/automation"
	scrapeproblemv1 "github.com/EthanKim8683/Competitive-Programming/Utility/gen/automation/scrape_problem/v1"
	"github.com/spf13/cobra"
)

var debugScrapeProblemCmd = &cobra.Command{
	Use:   "scrape-problem <url>",
	Short: "Scrape a problem",
	Long:  "Scrape a problem and output the inputs to standard output",
	Args:  cobra.ExactArgs(1),
	Run: func(cmd *cobra.Command, args []string) {
		url := args[0]

		request := &scrapeproblemv1.ScrapeProblemRequest{
			Url: url,
		}
		response := &scrapeproblemv1.ScrapeProblemResponse{}
		if err := automation.ScrapeProblem(request, response); err != nil {
			fmt.Fprintln(os.Stderr, err)
			os.Exit(1)
		}
		fmt.Println(response.Problem)
	},
}

func init() {
	RootCmd.AddCommand(debugScrapeProblemCmd)
}
