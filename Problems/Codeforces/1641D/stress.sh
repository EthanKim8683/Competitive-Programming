make sol
for ((i = 1; ; i++)); do
	echo "$i"
	time ./sol "$i" || break
done
