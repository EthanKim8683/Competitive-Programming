#!/bin/bash

function exe {
	echo "$TMPDIR/${1%%.*}"
}

function compile {
	g++-14 -o "$(exe $1)" "$1" -O2 -std=c++20 -DETHANKIM8683
}

function run {
	"$(exe $1)"
}

compile "sol.cpp" & compile "gen.cpp" & compile "check.cpp" & wait
mkfifo "p1" "p2" "p3" "p4"
run "gen.cpp" > "p1" & \
	cat "p1" | tee -a "p2" "p3" >/dev/null & \
	cat "p2" | run "sol.cpp" > "p4" & \
	cat "p3" "p4" | run "check.cpp" &
wait
rm "$(exe "sol.cpp")" "$(exe "gen.cpp")" "$(exe "check.cpp")" \
	"p1" "p2" "p3" "p4"
