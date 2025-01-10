#!/bin/bash

# Compiles and runs programs
# $1 = program path
# $2 = language (optional)

dir=$(dirname "$0")

"$("$dir/cached_compile.sh" "$1" "$2")"
