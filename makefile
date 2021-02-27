include makefile.base

CFLAGS = -D_4C_SHARE=\"$(_4C_SHARE)\"
ifdef DEBUG
CFLAGS += -Og -g -gdwarf-4 -fkeep-inline-functions -fPIC
else
CFLAGS += -O2 -fPIC
endif

OBJS=4cc.o file.o array.o syntax_tree.o type.o
LDLIBS=

all: 4cc doc tags

4cc: $(OBJS)

test: all
	./4cc tests/default.4c

doc:
	+$(MAKE) -C docs/ all

tags: $(OBJS)
	ctags -R

install: all
	install -s 4cc $(PREFIX)/bin/
	mkdir -p $(_4C_SHARE)/tests/
	install -m 644 tests/* $(_4C_SHARE)/tests/
	mkdir -p $(_4C_SHARE)/examples/
	install -m 644 examples/* $(_4C_SHARE)/examples/
	+$(MAKE) -C docs/ install

clean:
	rm -f 4cc $(OBJS)
	+$(MAKE) -C docs/ clean

