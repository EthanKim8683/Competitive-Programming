#!/bin/bash

function compile {
	local exe="$TMPDIR/${1%%.*}"
	g++-14 -o "$exe" "$1" -O2 -std=c++20 -DETHANKIM8683
}

function run {
	local exe="$TMPDIR/${1%%.*}"
	"$exe"
}

compile "sol.cpp" & compile "check.cpp" & compile "gen.cpp" & wait
run "sol.cpp" & run "check.cpp" & run "gen.cpp" & wait
