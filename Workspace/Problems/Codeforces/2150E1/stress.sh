make sol
wa=0
for ((t = 1; ; t++)); do
	./sol "$t" || ((wa++))
	echo "scale=3; $wa / $t" | bc
done
