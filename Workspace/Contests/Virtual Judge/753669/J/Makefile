INPUTS := $(wildcard inputs/*.txt)
OUTPUTS := $(patsubst inputs/%.txt, outputs/%.txt, $(INPUTS))

.PHONY: test clean force_test

outputs/%.txt: inputs/%.txt sol.py
	mkdir -p outputs
	python3 sol.py < $< > $@

test: $(OUTPUTS)

clean:
	rm -rf outputs

force_test:
	$(MAKE) clean
	$(MAKE) test