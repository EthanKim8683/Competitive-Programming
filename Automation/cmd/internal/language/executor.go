package language

import "io"

type Executor interface {
	Execute(executablePath string) (Execution, error)
}

type Execution struct {
	Stdout   *io.Reader
	Stderr   *io.Reader
	ExitCode chan int
}
