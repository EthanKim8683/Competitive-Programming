package commands

import (
	"fmt"
	"os"
	"path/filepath"

	"github.com/spf13/cobra"

	"github.com/EthanKim8683/Competitive-Programming/Utility/bundle/bundlers"
)

var (
	language string

	includeDirs []string
)

var bundleCmd = &cobra.Command{
	Use:   "bundle",
	Short: "Bundle a file for submission",
	Long:  "Output the amalgamation of a file and its local dependencies to standard output for submission",
	Run: func(cmd *cobra.Command, args []string) {
		path := args[0]

		if language == "" {
			ext := filepath.Ext(path)
			switch ext {
			case ".c":
				language = "c"
			case ".cpp":
				language = "c++"
			default:
				fmt.Fprintln(os.Stderr, fmt.Errorf("could not infer language from file extension: %s", ext))
				os.Exit(1)
			}
		}

		var (
			amalgamation string
			err          error
		)
		switch language {
		case "c":
			bundler := bundlers.NewCBundler(includeDirs)
			amalgamation, err = bundler.Bundle(args[0])
		case "c++":
			cppIncludeDirs := append(includeDirs, "/Users/ethankim8683/Competitive Programming/Libraries/cpp")
			bundler := bundlers.NewCBundler(cppIncludeDirs)
			amalgamation, err = bundler.Bundle(args[0])
		default:
			err = fmt.Errorf("unsupported language: %s", language)
		}
		if err != nil {
			fmt.Fprintln(os.Stderr, err)
			os.Exit(1)
		}
		fmt.Println(amalgamation)
	},
}

func init() {
	RootCmd.AddCommand(bundleCmd)

	bundleCmd.Flags().StringVarP(&language, "language", "l", "", "language of the file to bundle (c, c++)")
	bundleCmd.Flags().StringSliceVarP(&includeDirs, "include", "I", []string{}, "include directories to search for local dependencies")
}
