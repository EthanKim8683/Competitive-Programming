package judge

type Submitter interface {
	Submit(problemID string, codePath string) (string, error)
}
