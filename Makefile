COMPILE_FLAGS := compile_flags.txt

.PHONY: $(COMPILE_FLAGS)

$(COMPILE_FLAGS):
	echo "-D__float128=long double" > $(COMPILE_FLAGS)
	g++ -v -E -x c++ /dev/null -o /dev/null 2>&1 1>/dev/null \
		| grep -E '^[[:space:]][^[:space:]]+$$' \
		| xargs -n1 -I{} echo "-isystem{}" \
		>> $(COMPILE_FLAGS)