package automation

import (
	"fmt"

	automationv1 "github.com/EthanKim8683/Competitive-Programming/Utility/gen/automation/v1"
)

var (
	LanguageCPP20 = "c++20"
	LanguageCPP23 = "c++23"
)

func toLanguageEnum(language *string) (automationv1.SubmitRequest_Language, error) {
	languageEnum := automationv1.SubmitRequest_LANGUAGE_UNSPECIFIED
	var err error
	if language != nil {
		switch *language {
		case LanguageCPP20:
			languageEnum = automationv1.SubmitRequest_LANGUAGE_CPP20
		case LanguageCPP23:
			languageEnum = automationv1.SubmitRequest_LANGUAGE_CPP23
		default:
			err = fmt.Errorf("unsupported language: %s", *language)
		}
	}
	return languageEnum, err
}

func Submit(url string, body string, language *string) error {
	languageEnum, err := toLanguageEnum(language)
	if err != nil {
		return err
	}

	response := &automationv1.SubmitResponse{}
	if err := rpc(
		"automation.v1.submit",
		&automationv1.SubmitRequest{
			Url:      url,
			Body:     body,
			Language: &languageEnum,
		},
		response,
	); err != nil {
		return err
	}
	return nil
}
