.PHONY: clean

sol: sol.cpp
	g++ -o sol sol.cpp \
		-DETHANKIM8683 \
		-O2 \
		-std=c++20 \
		-I../../../include \
		-I/opt/homebrew/include \
		-L/opt/homebrew/lib \
		-lraylib \
		-framework IOKit \
		-framework Cocoa \
		-framework OpenGL

clean:
	rm -f sol
