INPUTS := $(wildcard inputs/*.txt)
OUTPUTS := $(patsubst inputs/%.txt, outputs/%.txt, $(INPUTS))

.PHONY: test clean force_test

sol: sol.cpp
	g++ -o sol sol.cpp \
		-DU=U \
		-D_GLIBCXX_DEBUG \
		-O0 \
		-g \
		-std=c++20 \
		-I../../../include \
		-I/opt/homebrew/include \
		-L/opt/homebrew/lib \
		-lraylib \
		-framework IOKit \
		-framework Cocoa \
		-framework OpenGL

outputs/%.txt: inputs/%.txt sol
	mkdir -p outputs
	time ./sol < $< > $@

test: $(OUTPUTS)

clean:
	rm -f sol
	rm -rf outputs

force_test:
	$(MAKE) clean
	$(MAKE) test
