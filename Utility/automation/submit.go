package automation

import (
	"fmt"

	automationv1 "github.com/EthanKim8683/Competitive-Programming/Utility/gen/automation/v1"
)

var (
	LanguageCPP20 = "c++20"
	LanguageCPP23 = "c++23"
)

type SubmitOptions struct {
	Language *string
}

func toLanguage(language *string) automationv1.SubmitRequest_Language {
	if language == nil {
		return automationv1.SubmitRequest_LANGUAGE_UNSPECIFIED
	}
	switch *language {
	case LanguageCPP20:
		return automationv1.SubmitRequest_LANGUAGE_CPP20
	case LanguageCPP23:
		return automationv1.SubmitRequest_LANGUAGE_CPP23
	default:
		panic(fmt.Errorf("unsupported language: %s", *language))
	}
}

func Submit(url string, body string, options SubmitOptions) error {
	language := toLanguage(options.Language)
	response := &automationv1.SubmitResponse{}
	if err := rpc(
		"automation.v1.submit",
		&automationv1.SubmitRequest{
			Url:      url,
			Body:     body,
			Language: &language,
		},
		response,
	); err != nil {
		return err
	}
	return nil
}
