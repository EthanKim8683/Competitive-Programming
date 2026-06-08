package commands

import (
	"fmt"

	"github.com/alecthomas/kong"
	"github.com/spf13/cobra"
)

type BundleCmd struct {
	Source string `arg:"" type:"path"`
}

var bundleCmd = &cobra.Command{
	Use:   "bundle",
	Short: "Bundle a submission",
	Args:  cobra.ExactArgs(1),
	Run: func(cmd *cobra.Command, args []string) {
		var cli BundleCmd
		parser, err := kong.New(&cli)
		if err != nil {
			panic(err)
		}
		ctx, err := parser.Parse(args)
		if err != nil {
			panic(err)
		}
		fmt.Println(ctx.Command())
	},
}

func init() {
	RootCmd.AddCommand(bundleCmd)
}
