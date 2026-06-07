package port

type Compiler interface {
	Compile(sourcePath string, executablePath string) error
}
