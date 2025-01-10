#!/bin/bash

# Compiles programs into executables, reusing cached executables when possible
# $1 = program path
# $2 = language (optional)

dir=$(dirname "$0")

[ ! -r "$1" ] \
	&& echo "File '$1' is not readable" && exit 1

# generate fingerprint based on the program's contents and language
fp="$(cat - "$1" <<< "$2" | sha256sum | cut -d' ' -f1)"

exe="$TMPDIR/$fp"
if [ ! -d "$exe" ]; then
	"$dir/compile.sh" "$1" "$exe" "$2" || exit 1
fi
printf "$exe"
