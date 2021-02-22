include ../makefile.base
DOCS=4c_lang.html

all: $(DOCS)

.SUFFIXES: .md .html
.md.html:
	markdown $^ > $@

install: all
	mkdir -p $(FOURC_SHARE)/docs/
	install -m 644 docs/*.html $(FOURC_SHARE)/docs

clean:
	rm -f $(DOCS)

