#!/bin/bash

pnpm build
T="$(./time.sh sh "target.sh" | bc)"
t="$(./time.sh node "dist/index.js" | bc)"
echo "T=$T, t=$t"
if [[ $t > $T ]]; then
	echo "slower by $(bc <<< "$t - $T")s"
else
	echo "faster by $(bc <<< "$T - $t")s"
fi
