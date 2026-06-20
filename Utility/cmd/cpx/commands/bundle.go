package commands

import (
	"fmt"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/bundler"
	"github.com/spf13/cobra"
)

var bundleCmd = &cobra.Command{
	Use: "bundle",
	Run: func(cmd *cobra.Command, args []string) {
		sourcePath := args[0]

		cBundler := bundler.NewC(
			[]string{
				"~/Competitive-Programming/include",
			},
		)

		bundle, err := cBundler.Bundle(sourcePath)
		if err != nil {
			fmt.Println("error bundling:", err)
			return
		}
		fmt.Println(bundle)
	},
}

func init() {
	RootCmd.AddCommand(bundleCmd)
}
