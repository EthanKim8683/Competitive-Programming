INPUTS := $(wildcard inputs/*.txt)
OUTPUTS := $(patsubst inputs/%.txt, outputs/%.txt, $(INPUTS))

.PHONY: test clean force_test

sol: sol.cpp
	g++ -o sol sol.cpp \
		-DU=U \
		-O2 \
		-std=c++17 \
		-I../../../../include \
		-I/opt/homebrew/include \
		-L/opt/homebrew/lib \
		-lraylib \
		-framework IOKit \
		-framework Cocoa \
		-framework OpenGL

outputs/%.txt: inputs/%.txt sol
	mkdir -p outputs
	./sol < $< > $@

test: $(OUTPUTS)

bundle: sol.cpp
	cpx bundle sol.cpp > bundled.cpp

clean:
	rm -f sol
	rm -rf outputs

force_test:
	$(MAKE) clean
	$(MAKE) test
