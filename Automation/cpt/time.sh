#!/bin/bash

output="$(/usr/bin/time ${@:1} 2>&1)"
user="$(ggrep -Po '\d+\.\d+(?= user)' <<< "$output")"
sys="$(ggrep -Po '\d+\.\d+(?= sys)' <<< "$output")"
echo "$(bc <<< "$user + $sys")"
