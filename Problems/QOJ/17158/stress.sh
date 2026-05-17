make sol
for ((i = 1; ; i++)); do
	echo "$i"
	./sol "$i" || break
done
