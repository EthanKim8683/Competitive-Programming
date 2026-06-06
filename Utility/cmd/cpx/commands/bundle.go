package commands

import (
	"fmt"
	"os"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/command"
	"github.com/spf13/cobra"
)

var (
	bundleLanguageProvider = &command.LanguageProvider{
		LanguageFlagUsage: "language to bundle as",
	}
	bundleBundlerProvider = &command.BundlerProvider{
		LanguageProvider: bundleLanguageProvider,
	}
)

var bundleCmd = &cobra.Command{
	Use:   "bundle",
	Short: "Bundle a submission",
	Args:  cobra.ExactArgs(1),
	Run: func(cmd *cobra.Command, args []string) {
		bundleLanguageProvider.FilePath = &args[0]

		filePath := args[0]

		bundler, err := bundleBundlerProvider.Bundler()
		if err != nil {
			fmt.Fprintln(os.Stderr, err)
			os.Exit(1)
		}

		bytes, err := os.ReadFile(filePath)
		if err != nil {
			fmt.Fprintln(os.Stderr, err)
			os.Exit(1)
		}
		source := string(bytes)

		if bundler != nil {
			source, err = bundler.Bundle(source)
			if err != nil {
				fmt.Fprintln(os.Stderr, err)
				os.Exit(1)
			}
		}

		fmt.Println(source)
	},
}

func init() {
	RootCmd.AddCommand(bundleCmd)

	bundleLanguageProvider.Bind(bundleCmd)
	bundleBundlerProvider.Bind(bundleCmd)
}
