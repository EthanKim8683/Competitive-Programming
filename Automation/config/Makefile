include ../../Makefile.Common

TEMPLATES := $(wildcard *.template)
TARGETS := $(patsubst %.template, %, $(TEMPLATES))

.PHONY: envsubst clean

%: %.template
	envsubst < $< > $@

envsubst: $(TARGETS)

clean:
	rm $(TARGETS)