package codeforces

import (
	"context"
	"fmt"
	"strings"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/browser"
	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/domain"
	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/port"
	"github.com/PuerkitoBio/goquery"
)

func parseProblemType(d *goquery.Document) (domain.ProblemType, error) {
	var (
		hasFirstRun    = false
		hasSecondRun   = false
		hasInteraction = false
		hasInput       = false
		hasOutput      = false
	)
	d.Find("div.section-title, span.tex-font-style-bf").
		Each(func(_ int, s *goquery.Selection) {
			switch strings.TrimSpace(s.Text()) {
			case "First Run":
				hasFirstRun = true
			case "Second Run":
				hasSecondRun = true
			case "Interaction":
				hasInteraction = true
			case "Input":
				hasInput = true
			case "Output":
				hasOutput = true
			}
		})

	switch {
	case hasFirstRun && hasSecondRun:
		return domain.ProblemTypeStdioRunTwice, nil
	case hasInteraction:
		return domain.ProblemTypeStdioInteractive, nil
	case hasInput && hasOutput:
		return domain.ProblemTypeStdioBatch, nil
	default:
		return domain.ProblemTypeUnspecified, fmt.Errorf("could not determine problem type")
	}
}

func parseStdioBatch(d *goquery.Document) *domain.StdioBatch {
	inputs := d.Find("div.input pre").
		Map(func(_ int, s *goquery.Selection) string {
			return browser.InnerText(s)
		})
	outputs := d.Find("div.output pre").
		Map(func(_ int, s *goquery.Selection) string {
			return browser.InnerText(s)
		})
	return &domain.StdioBatch{
		Inputs:  inputs,
		Outputs: outputs,
	}
}

func parseProblem(d *goquery.Document) (*domain.Problem, error) {
	problemType, err := parseProblemType(d)
	if err != nil {
		return nil, fmt.Errorf("could not parse problem type: %w", err)
	}

	problem := &domain.Problem{
		Type: problemType,
	}
	switch problemType {
	case domain.ProblemTypeStdioBatch:
		problem.StdioBatch = parseStdioBatch(d)
	case domain.ProblemTypeStdioInteractive:
	case domain.ProblemTypeStdioRunTwice:
	default:
		return nil, fmt.Errorf("unexpected problem type: %s", problemType)
	}
	return problem, nil
}

func (c *Codeforces) ScrapeProblem(ctx context.Context, url string) (*domain.Problem, error) {
	b := c.browser.Context(ctx)

	page, err := browser.Page(b, url)
	if err != nil {
		return nil, fmt.Errorf("could not open page: %w", err)
	}

	if err = page.WaitLoad(); err != nil {
		return nil, fmt.Errorf("could not wait for page to load: %w", err)
	}

	d, err := browser.Document(page)
	if err != nil {
		return nil, fmt.Errorf("could not create document: %w", err)
	}

	problem, err := parseProblem(d)
	if err != nil {
		return nil, fmt.Errorf("could not parse problem: %w", err)
	}
	problem.URL = url
	return problem, nil
}

var _ port.ProblemScraper = (*Codeforces)(nil)
