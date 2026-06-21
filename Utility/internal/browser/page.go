package browser

import (
	"fmt"
	"strings"

	"github.com/PuerkitoBio/goquery"
	"github.com/go-rod/rod"
	"github.com/go-rod/rod/lib/proto"
)

func Page(b *rod.Browser, url string) (*rod.Page, error) {
	return b.Page(proto.TargetCreateTarget{
		URL: url,
	})
}

func Document(p *rod.Page) (*goquery.Document, error) {
	html, err := p.HTML()
	if err != nil {
		return nil, fmt.Errorf("could not get HTML: %w", err)
	}

	d, err := goquery.NewDocumentFromReader(strings.NewReader(html))
	if err != nil {
		return nil, fmt.Errorf("could not create document: %w", err)
	}

	return d, nil
}

func InnerText(s *goquery.Selection) string {
	return ""
}
