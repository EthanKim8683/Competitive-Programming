INPUTS := $(wildcard inputs/*.txt)
OUTPUTS := $(patsubst inputs/%.txt, outputs/%.txt, $(INPUTS))

.PHONY: test clean

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

test: sol
	./sol

clean:
	rm -f sol