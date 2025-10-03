.PHONY: envsubst clean

TEMPLATES := $(wildcard *.template)
TARGETS := $(patsubst %.template, %, $(TEMPLATES))

%: %.template
	envsubst < $< > $@

envsubst: $(TARGETS)

clean:
	rm $(TARGETS)