package snippet

import (
	"github.com/EthanKim8683/Competitive-Programming/Utility/cmd/cpx/commands"
	"github.com/spf13/cobra"
)

var snippetCmd = &cobra.Command{
	Use:   "snippet",
	Short: "Snippet management",
}

func init() {
	commands.RootCmd.AddCommand(snippetCmd)
}
