package language

type Compiler interface {
	Compile(contents string, options map[string]string) (string, error)
}
