.PHONY: test clean force_test

sol: sol.cpp
	g++ -o sol sol.cpp \
		-DETHANKIM8683 \
		-DU=U \
		-D_GLIBCXX_DEBUG \
		-O0 \
		-g \
		-std=c++20 \
		-I../../../../Libraries/cpp \
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
