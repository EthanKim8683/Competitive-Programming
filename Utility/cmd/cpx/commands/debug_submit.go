package commands

import (
	"github.com/spf13/cobra"
)

var language2 *string

var debugSubmitCmd = &cobra.Command{
	Use:   "submit <url> <body>",
	Short: "Submit a solution",
	Long:  "Submit a solution and output the verdict",
	Args:  cobra.ExactArgs(2),
	Run: func(cmd *cobra.Command, args []string) {
		// url, body := args[0], args[1]

		// request := &submitv1.SubmitRequest{
		// 	Url:      url,
		// 	Source:   body,
		// 	Language: language2,
		// }
		// response := &submitv1.SubmitResponse{}
		// if err := automation.Submit(request, response); err != nil {
		// 	fmt.Fprintln(os.Stderr, err)
		// 	os.Exit(1)
		// }
		// fmt.Println(response.Submission)
	},
}

func init() {
	RootCmd.AddCommand(debugSubmitCmd)

	debugSubmitCmd.Flags().StringVarP(&language, "language", "l", "", "language of the solution to submit (cpp20, cpp23)")
}
