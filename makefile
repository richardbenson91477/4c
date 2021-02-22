include makefile.base

CFLAGS = -DFOURC_SHARE=\"$(FOURC_SHARE)\"
ifdef DEBUG
CFLAGS += -Og -g -gdwarf-4 -fkeep-inline-functions -fPIC
else
CFLAGS += -O2 -fPIC
endif

OBJS=4cc.o
LDLIBS=

all: 4cc doc

4cc: $(OBJS)

test: all
	./4cc tests/default.4c

doc:
	+$(MAKE) -C docs/ all

install: all
	install -s 4cc $(PREFIX)/bin/
	mkdir -p $(FOURC_SHARE)/tests/
	install -m 644 tests/* $(FOURC_SHARE)/tests/
	mkdir -p $(FOURC_SHARE)/examples/
	install -m 644 examples/* $(FOURC_SHARE)/examples/
	+$(MAKE) -C docs/ install

clean:
	rm -f 4cc $(OBJS)
	+$(MAKE) -C docs/ clean

