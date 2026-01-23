.PHONY: clean

sol: grader.cpp sol.cpp
	g++ -o sol grader.cpp sol.cpp \
		-DETHANKIM8683 \
		-O2 \
		-std=c++20 \
		-I../../../Libraries/cpp \
		-I/opt/homebrew/include \
		-L/opt/homebrew/lib \
		-lraylib \
		-framework IOKit \
		-framework Cocoa \
		-framework OpenGL

clean:
	rm -f sol
