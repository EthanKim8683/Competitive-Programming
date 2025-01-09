#!/bin/bash

# Compiles and runs programs
# $1 = program path
# $2 = language (optional)

[ ! -r "$1" ] \
	&& echo "file '$1' is not readable" && exit 1

# generate fingerprint based on the program's contents and language to allow
# caching of executables
fp="$(cat - "$1" <<< "$2" | sha256sum | cut -d' ' -f1)"

tmp="$TMPDIR/$fp"
if [ ! -f "$tmp" ]; then
	./compile.sh "$1" "$tmp" "$2" || exit 1
fi

"$tmp"
