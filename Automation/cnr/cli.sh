#!/bin/bash

# CLI for cnr.sh
# $1 = program path
# $2 = language (optional)

# TODO: Interface

dir=$(dirname "$0")

cpdir="$HOME/Desktop/Competitive-Programming"
( [ -z "$1" ] || [[ "$(realpath "$1")" != "$cpdir"/* ]] ) \
	&& echo "Program must be located in directory '$cpdir'" 1>&2 && exit 1

"$dir/cnr.sh" "$1" "$2" || exit 1
