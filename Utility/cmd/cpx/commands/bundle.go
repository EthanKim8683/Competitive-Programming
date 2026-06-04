package commands

import (
	"fmt"

	"github.com/spf13/cobra"
)

var bundleCmd = &cobra.Command{
	Use:   "bundle",
	Short: "Bundle a submission",
	Run: func(cmd *cobra.Command, args []string) {
		fmt.Println("bundle called")
	},
}

func init() {
	RootCmd.AddCommand(bundleCmd)
}
