package domain

type Language int

const (
	LanguageUnspecified Language = iota
	LanguageCpp17
	LanguageCpp20
	LanguageCpp23
)
