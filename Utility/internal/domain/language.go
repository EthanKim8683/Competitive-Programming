package domain

type Language string

const (
	LanguageUnspecified Language = ""
	LanguageCxx17       Language = "c++17"
	LanguageCxx20       Language = "c++20"
	LanguageCxx23       Language = "c++23"
	LanguagePython3     Language = "python3"
)
