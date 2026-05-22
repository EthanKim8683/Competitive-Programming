.PHONY: clean

sol: sol.cpp
	g++ -o sol sol.cpp \
		-DU=U \
		-D_GLIBCXX_DEBUG \
		-O0 \
		-std=c++20 \
		-I../../../include \
		-I/opt/homebrew/include \
		-L/opt/homebrew/lib \
		-lraylib \
		-framework IOKit \
		-framework Cocoa \
		-framework OpenGL

test: sol
	./sol

clean:
	rm -f sol
