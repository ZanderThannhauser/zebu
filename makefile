
CC = gcc

CPPFLAGS += -D _GNU_SOURCE
CPPFLAGS += -I .

CFLAGS += -Wall -Werror -Wfatal-errors

buildtype ?= release

ifeq ($(buildtype), release)
CPPFLAGS += -D RELEASE

CFLAGS += -O2
CFLAGS += -flto

LDFLAGS += -flto=auto

else ifeq ($(buildtype), test)
CPPFLAGS += -D TESTING

CFLAGS += -g
CFLAGS += -Wno-unused-variable
CFLAGS += -Wno-unused-function
CFLAGS += -Wno-unused-but-set-variable
CFLAGS += -Wno-unused-label

else ifeq ($(buildtype), debug)
CPPFLAGS += -D DEBUGGING

CFLAGS += -g
CFLAGS += -Wno-unused-variable
CFLAGS += -Wno-unused-function
CFLAGS += -Wno-unused-but-set-variable
CFLAGS += -Wno-unused-label

#CFLAGS += -pg
#LDFLAGS += -pg

else
$(error "invalid buildtype!");
endif

verbose ?= yes
ifeq ($(verbose), yes)
CPPFLAGS += -D VERBOSE
else ifeq ($(verbose), no)
else
$(error "invalid verbose!");
endif

arenas ?= without
ifeq ($(arenas), with)
CPPFLAGS += -D WITH_ARENAS
else ifeq ($(arenas), without)
CPPFLAGS += -D WITHOUT_ARENAS
else
$(error "invalid arenas!");
endif

dotout ?= no
ifeq ($(dotout), yes)
CPPFLAGS += -D DOTOUT
else ifeq ($(dotout), no)
else
$(error "invalid dotout!");
endif

on_error ?= do_nothing
ifeq ($(on_error), do_nothing)
ON_ERROR =
else ifeq ($(on_error), open_editor)
ON_ERROR += || ($$EDITOR $<; false)
else
$(error "invalid on_error option!");
endif

buildprefix = gen/$(buildtype)-build/$(verbose)-verbose/$(arenas)-arenas/$(dotout)-dotout

default: $(buildprefix)/zebu

#ARGS += -v
ARGS += --verbose

#ARGS += -l
ARGS += --minimize-lexer

#ARGS += --yacc=readline-debug -i ./-examples/classic/classic.zb -o ./-examples/classic/classic

#ARGS += --yacc=readline -i ./-examples/math/math.zb -o ./-examples/math/math
#ARGS += --yacc=readline-debug -i ./-examples/math/math.zb -o ./-examples/math/math

#ARGS += --yacc=fileio-graphviz -i ./-examples/maia/maia.zb -o ./-examples/maia/maia
#ARGS += --yacc=fileio-passfail -i ./-examples/maia/maia.zb -o ./-examples/maia/maia
#ARGS += --yacc=readline-debug -i ./-examples/json/json.zb -o ./-examples/json/json
#ARGS += --yacc=readline-debug -i ./-examples/C-expressions/C.zb -o ./-examples/C-expressions/output
#ARGS += --yacc=readline-debug -i ./-examples/explode/explode.zb -o ./-examples/explode/explode
#ARGS += --yacc=readline-debug -i ./-examples/gegex/gegex.zb -o ./-examples/gegex/output
#ARGS += --yacc=readline-debug -i ./-examples/hard/hard.zb -o ./-examples/hard/output

#ARGS += --yacc=fileio-graphviz -i ./-examples/C/C.zb -o ./-examples/C/C
#ARGS += --yacc=readline-debug -i ./-examples/C/C.zb -o ./-examples/C/C
#ARGS += --yacc=readline-debug -i ./-examples/lisp/lisp.zb -o ./-examples/lisp/lisp

#ARGS += --yacc=fileio-passfail -i ./-examples/iloc/iloc.zb -o ./-examples/iloc/iloc
#ARGS += --yacc=fileio-debug -i ./-examples/iloc/iloc.zb -o ./-examples/iloc/iloc
#ARGS += --yacc=fileio-passfail -i ./-examples/iloc/iloc2.zb -o ./-examples/iloc/iloc
#ARGS += --yacc=fileio-debug -i ./-examples/iloc/iloc2.zb -o ./-examples/iloc/iloc
#ARGS += --yacc=fileio-passfail -i ./-examples/iloc/iloc3.zb -o ./-examples/iloc/iloc
#ARGS += --yacc=fileio-debug -i ./-examples/iloc/iloc3.zb -o ./-examples/iloc/iloc

#ARGS += --yacc=readline-debug -i ./-examples/xml/xml.zb -o ./-examples/xml/xml

run: $(buildprefix)/zebu
	$< $(ARGS)

valrun: $(buildprefix)/zebu
	valgrind $< $(ARGS)

valrun-stop: $(buildprefix)/zebu
	valgrind --gen-suppressions=yes -- $< ${ARGS}

valrun-leak: $(buildprefix)/zebu
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -- $< ${ARGS}

tracerun: $(buildprefix)/zebu
	strace $< $(ARGS)

install: $(buildprefix)/zebu
	@ mkdir -vp ~/bin/
	@ cp -vau $(buildprefix)/zebu ~/bin/zebu

.PRECIOUS: %/

%/:
	@ mkdir -p $@

gen/srclist.mk: | gen/%/
	@ echo "searching for source files..."
	@ find -name '*.c' -! -path '*/-*' | sort -Vr | sed 's/^/srcs += /' > $@

ifneq "$(MAKECMDGOALS)" "clean"
include gen/srclist.mk

srcs += ./out/escaped/just_tables_source.c     ./out/escaped/just_tables_header.c
srcs += ./out/escaped/buffer_driven_source.c   ./out/escaped/buffer_driven_header.c
srcs += ./out/escaped/readline_source.c        ./out/escaped/readline_header.c
srcs += ./out/escaped/readline_debug_source.c  ./out/escaped/readline_debug_header.c
srcs += ./out/escaped/fileio_debug_source.c    ./out/escaped/fileio_debug_header.c
srcs += ./out/escaped/fileio_passfail_source.c ./out/escaped/fileio_passfail_header.c
srcs += ./out/escaped/fileio_graphviz_source.c ./out/escaped/fileio_graphviz_header.c

endif

objs := $(patsubst %.c,$(buildprefix)/%.o,$(srcs))
objs := $(patsubst %.S,$(buildprefix)/%.o,$(objs))

deps := $(patsubst %.c,$(buildprefix)/%.d,$(srcs))
deps := $(patsubst %.S,$(buildprefix)/%.d,$(deps))

$(buildprefix)/%.o $(buildprefix)/%.d: %.c | $(buildprefix)/%/
	@ echo "compiling $<"
	@ $(CC) -c $(CPPFLAGS) $(CFLAGS) $< -MD -o $(buildprefix)/$*.o $(ON_ERROR)

$(buildprefix)/zebu: $(objs)
	@ echo "linking $@"
	@ $(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@

$(buildprefix)/escape: ./-escape.c | $(buildprefix)/
	@ echo "compiling $<"
	@ $(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) ./$< $(LOADLIBES) $(LDLIBS) -o $@

.PRECIOUS: ./out/escaped/%_source.c
.PRECIOUS: ./out/escaped/%_header.c

./out/escaped/%_source.c: $(buildprefix)/escape ./out/-templates/%.c
	@ echo "escaping $*"
	@ $^ -v $*_source -o $@

./out/escaped/%_header.c: $(buildprefix)/escape ./out/-templates/%.h
	@ echo "escaping $*"
	@ $^ -v $*_header -o $@

dot/%.png: dot/%.dot
	dot -Tpng < $< > $@

clean:
	for l in $$(cat .gitignore); do rm -rvf $$l; done

ifneq "$(MAKECMDGOALS)" "clean"
include $(deps)
endif
















