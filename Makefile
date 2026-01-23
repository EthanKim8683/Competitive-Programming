compile_flags.txt:
	echo "-I/opt/homebrew/include" >> compile_flags.txt
	echo "-ILibraries/cpp" >> compile_flags.txt
	echo "-DETHANKIM8683" >> compile_flags.txt
	echo "-std=c++23" >> compile_flags.txt
	echo "-D__float128=long double" >> compile_flags.txt
	g++ -v -E -x c++ /dev/null -o /dev/null 2>&1 1>/dev/null \
		| grep -E '^[[:space:]][^[:space:]]+$$' \
		| xargs -n1 -I{} echo "-isystem{}" \
		>> compile_flags.txt
