package codeforces

import (
	"context"
	"fmt"
	"strings"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/domain"
	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/port"
	"github.com/go-rod/rod"
)

func sectionTitle(title string) string {
	return fmt.Sprintf(`//div[contains(@class, 'section-title') and normalize-space()=%q]`, title) + "|" +
		fmt.Sprintf(`//span[contains(@class, 'tex-font-style-bf') and normalize-space()=%q]`, title)
}

func problemType(page *rod.Page) (domain.ProblemType, error) {
	switch {
	case page.MustHasX(sectionTitle("First Run")) &&
		page.MustHasX(sectionTitle("Second Run")):
		return domain.ProblemTypeCommunication, nil
	case page.MustHasX(sectionTitle("Interaction")):
		return domain.ProblemTypeInteractive, nil
	case page.MustHasX(sectionTitle("Input")) &&
		page.MustHasX(sectionTitle("Output")):
		return domain.ProblemTypeBatch, nil
	default:
		return domain.ProblemTypeUnspecified, fmt.Errorf("could not determine problem type")
	}
}

func scrapeBatchProblem(page *rod.Page) (*domain.BatchProblem, error) {
	inputElements := page.MustElements(".input pre")
	inputs := make([]string, 0, len(inputElements))
	for _, inputElement := range inputElements {
		inputs = append(inputs, strings.TrimSpace(inputElement.MustText()))
	}

	outputElements := page.MustElements(".output pre")
	outputs := make([]string, 0, len(outputElements))
	for _, outputElement := range outputElements {
		outputs = append(outputs, strings.TrimSpace(outputElement.MustText()))
	}

	if len(inputs) != len(outputs) {
		return nil, fmt.Errorf("input and output count do not match: %d != %d", len(inputs), len(outputs))
	}

	return &domain.BatchProblem{
		Inputs:  inputs,
		Outputs: outputs,
	}, nil
}

func (c *Codeforces) ScrapeProblem(ctx context.Context, url string) (p domain.Problem, err error) {
	defer func() {
		if r := recover(); r != nil {
			p = domain.Problem{}
			err = fmt.Errorf("panic: %+v", r)
		}
	}()

	page := c.browser.
		Context(ctx).
		MustPage(url)
	page.MustWaitLoad()
	defer page.MustClose()

	p.URL = url

	pType, err := problemType(page)
	if err != nil {
		return domain.Problem{}, err
	}
	p.Type = pType

	switch pType {
	case domain.ProblemTypeBatch:
		p.Batch, err = scrapeBatchProblem(page)
		if err != nil {
			return domain.Problem{}, err
		}
	case domain.ProblemTypeInteractive:
		p.Interactive = &domain.InteractiveProblem{}
	case domain.ProblemTypeCommunication:
		p.Communication = &domain.CommunicationProblem{}
	default:
		return domain.Problem{}, fmt.Errorf("unsupported problem type: %s", pType)
	}
	return p, nil
}

var _ port.ProblemScraper = (*Codeforces)(nil)
