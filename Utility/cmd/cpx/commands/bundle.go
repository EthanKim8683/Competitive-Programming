package commands

import (
	"fmt"

	"github.com/alecthomas/kong"
	"github.com/spf13/cobra"
)

type BundleCmd struct {
	Gxx struct {
		Flag string
	} `cmd:"" name:"g++"`

	Python3 struct {
		Flag string
	} `cmd:"" name:"python3"`
}

var bundleCmd = &cobra.Command{
	Use:   "bundle",
	Short: "Bundle a submission",
	Run: func(cmd *cobra.Command, args []string) {
		var cli BundleCmd
		k, err := kong.New(&cli)
		if err != nil {
			panic("error creating kong parser: " + err.Error())
		}
		ctx, err := k.Parse(args)
		if err != nil {
			panic("error parsing arguments: " + err.Error())
		}
		fmt.Println(ctx.Command())
	},
}

func init() {
	RootCmd.AddCommand(bundleCmd)
}
