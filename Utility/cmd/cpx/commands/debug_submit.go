package commands

import (
	"fmt"
	"os"

	"github.com/EthanKim8683/Competitive-Programming/Utility/automation"
	"github.com/spf13/cobra"
)

var language2 *string

var debugSubmitCmd = &cobra.Command{
	Use:   "submit <url> <body>",
	Short: "Submit a solution",
	Long:  "Submit a solution and output the verdict",
	Args:  cobra.ExactArgs(2),
	Run: func(cmd *cobra.Command, args []string) {
		url, body := args[0], args[1]
		err := automation.Submit(url, body, language2)
		if err != nil {
			fmt.Fprintln(os.Stderr, err)
			os.Exit(1)
		}
	},
}

func init() {
	RootCmd.AddCommand(debugSubmitCmd)

	debugSubmitCmd.Flags().StringVarP(&language, "language", "l", "", "language of the solution to submit (cpp20, cpp23)")
}
