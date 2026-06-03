package commands

import (
	"fmt"
	"os"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/onlinejudge"
	"github.com/spf13/cobra"
)

var debugScrapeProblemCmd = &cobra.Command{
	Use:   "dsp",
	Short: "Debug scrape problem",
	Args:  cobra.ExactArgs(1),
	Run: func(cmd *cobra.Command, args []string) {
		url := args[0]
		oj, err := onlinejudge.Resolve(url)
		if err != nil {
			fmt.Fprintln(os.Stderr, err)
			os.Exit(1)
		}
		if oj.ScrapeProblem == nil {
			fmt.Fprintln(os.Stderr, "ScrapeProblem is not implemented")
			os.Exit(1)
		}
		problem, err := oj.ScrapeProblem(url)
		if err != nil {
			fmt.Fprintln(os.Stderr, err)
			os.Exit(1)
		}
		fmt.Println(problem)
	},
}

func init() {
	RootCmd.AddCommand(debugScrapeProblemCmd)
}
