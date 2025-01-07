#!/opt/homebrew/bin/bash

function infer_language_using_filename {
	local rv=""

	# if filename is in basename.language.ext format
	rv="$(ggrep -Po '(?<=\.)\w+(?=\.\w+$)' <<< "$1")"
	[ -n "$rv" ] && echo "$rv" && return

	# based on file extension
	local ext="${1##*.}"
	case "$ext" in
		cpp) echo "cpp"; return ;;
		py) echo "python3"; return ;;
	esac

	echo "could not infer language of ${1@Q}" 1>&2
	return 1
}

infer_language_using_filename "$1"
