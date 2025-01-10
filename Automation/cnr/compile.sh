#!/opt/homebrew/bin/bash

# Compiles programs into executables
# $1 = program path
# $2 = executable path
# $3 = language (optional)

# $1 = filename
function infer_language_using_filename {
	# if filename is in name.lang.ext format
	local match="$(ggrep -Po '(?<=\.)\w+(?=\.\w+$)' <<< "$1")"
	[ -n "$match" ] && echo "$match" && return

	# based on file extension
	local ext="${1##*.}"
	case "$ext" in
		cpp) echo "cpp20" && return ;;
		py) echo "python3" && return ;;
	esac

	echo "Could not infer language of file '$1'" 1>&2
	exit 1
}

# $1 = program path
# $2 = executable path
# $3 = std (optional)
function compile_cpp {
	local std_arg=""
	[ -n "$3" ] && std_arg="-std=$3"

	g++-14 -o "$2" "$1" "$std_arg" -O2 -DETHANKIM8683 \
		|| exit 1
}

# $1 = program path
# $2 = executable path
function compile_python3 {
	[ ! -r "$1" ] \
		&& echo "File '$1' is not readable" 1>&2 && exit 1
	[ -f "$2" ] && [ ! -w "$2" ] \
		&& echo "File '$2' is not writable" 1>&2 && exit 1

	printf $"#!/opt/homebrew/bin/python3\n\n" > "$2" \
		&& cat "$1" >> "$2" \
		|| ( echo "Could not write to file '$2'" 1>&2 && exit 1 )
	chmod u+x "$2" \
		|| ( echo "Could not mark file '$2' as executable" 1>&2 && exit 1 )
}

[ -z "$3" ] \
	&& lang="$(infer_language_using_filename "$1")" \
	|| lang="$3"

case "$lang" in
	cpp) compile_cpp "$1" "$2" ;;
	cpp17) compile_cpp "$1" "$2" "c++17" ;;
	cpp20) compile_cpp "$1" "$2" "c++20" ;;
	cpp23) compile_cpp "$1" "$2" "c++23" ;;
	python3) compile_python3 "$1" "$2" ;;
	*) echo "Unknown language '$lang'" && exit 1 ;;
esac
