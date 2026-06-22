compile_flags.txt:
	rm -f compile_flags.txt
	echo "-U__block" >> compile_flags.txt
	echo "-isystem/opt/homebrew/include" >> compile_flags.txt
	echo "-D__float128=long double" >> compile_flags.txt
	g++ -v -E -x c++ /dev/null -o /dev/null 2>&1 1>/dev/null \
		| grep -E '^[[:space:]][^[:space:]]+$$' \
		| xargs -n1 -I{} echo "-isystem{}" \
		>> compile_flags.txt
	echo "-DETHANKIM8683" >> compile_flags.txt
	echo "-I./include" >> compile_flags.txt
	echo "-std=c++23" >> compile_flags.txt

clean:
	rm -f compile_flags.txt

.PHONY: clean