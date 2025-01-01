#!/bin/bash

g++-14 -O2 -std=c++20 -DETHANKIM8683 -o "sol" "sol.cpp" & g++-14 -O2 -std=c++20 -DETHANKIM8683 -o "check" "check.cpp" & wait
"./sol" < "inputs/1.txt" | cat "inputs/1.txt" - | "./check" & "./sol" < "inputs/2.txt" | cat "inputs/2.txt" - | "./check" & wait
