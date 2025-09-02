package language

type MetadataExtractor interface {
	ExtractMetadata(contents string) (string, error)
}
