INPUTS := $(wildcard inputs/*.txt)
OUTPUTS := $(patsubst inputs/%.txt, outputs/%.txt, $(INPUTS))

.PHONY: test clean force_test

sol: sol.cpp
	g++ -o sol sol.cpp \
		-DETHANKIM8683 \
		-DU=U \
		-D_GLIBCXX_DEBUG \
		-O0 \
		-g \
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
	for output in outputs/*.txt; do cat $$output; done

clean:
	rm -f sol
	rm -rf outputs

force_test:
	$(MAKE) clean
	$(MAKE) test
