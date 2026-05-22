INPUTS := $(wildcard inputs/*.txt)
OUTPUTS := $(patsubst inputs/%.txt, outputs/%.txt, $(INPUTS))

.PHONY: test clean force_test

sol: sol.cpp
	g++ -o sol sol.cpp \
		-DETHANKIM8683 \
		-Ofast \
		-std=c++17 \
		-I../../../include \
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

clean:
	rm -f sol
	rm -rf outputs

force_test:
	$(MAKE) clean
	$(MAKE) test
