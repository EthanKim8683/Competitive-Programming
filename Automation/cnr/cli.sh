#!/bin/bash

# CLI command for cnr.sh
# $1 = program path
# $2 = language (optional)

cpdir="$HOME/Desktop/Competitive-Programming"
( [ -z "$1" ] || [[ "$(realpath "$1")" != "$cpdir"/* ]] ) \
	&& echo "program must be located in directory '$cpdir'" 1>&2 && exit 1

./cnr.sh "$1" "$2" || exit 1
