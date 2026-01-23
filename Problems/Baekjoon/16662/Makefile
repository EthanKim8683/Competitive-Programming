.PHONY: test clean force_test

sol: sol.cpp
	g++ -o sol sol.cpp \
		-DETHANKIM8683 \
		-O2 \
		-std=c++17 \
		-I../../../Libraries/cpp \
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

force_test:
	$(MAKE) clean
	$(MAKE) test
