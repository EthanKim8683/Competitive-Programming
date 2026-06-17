package domain

type ProblemType string

const (
	ProblemTypeUnspecified   ProblemType = ""
	ProblemTypeBatch         ProblemType = "batch"
	ProblemTypeInteractive   ProblemType = "interactive"
	ProblemTypeCommunication ProblemType = "communication"
)

type BatchProblem struct {
	Inputs  []string
	Outputs []string
}

type InteractiveProblem struct{}

type CommunicationProblem struct{}

type Problem struct {
	URL           string
	Type          ProblemType
	Batch         *BatchProblem
	Interactive   *InteractiveProblem
	Communication *CommunicationProblem
}
