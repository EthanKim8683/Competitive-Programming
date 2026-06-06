package port

import "github.com/EthanKim8683/Competitive-Programming/Utility/internal/domain"

type LanguageProvider interface {
	Language() (domain.Language, error)
}
