#!/bin/bash

# Compiles programs into executables, reusing cached executables when possible
# $1 = program path
# $2 = language (optional)

[ ! -r "$1" ] \
	&& echo "File '$1' is not readable" && exit 1

# generate fingerprint based on the program's contents and language
fp="$(cat - "$1" <<< "$2" | sha256sum | cut -d' ' -f1)"

tmp="$TMPDIR/$fp"
if [ ! -f "$tmp" ]; then
	./compile.sh "$1" "$tmp" "$2" || exit 1
fi

echo "$tmp"
