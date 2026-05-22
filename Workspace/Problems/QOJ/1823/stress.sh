make sol
for ((i=1; ; i++)); do
	echo "$i"
	time ./sol "$i" > /dev/null || break
done
