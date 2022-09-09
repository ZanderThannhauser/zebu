
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

buildprefix = gen/$(buildtype)-build/$(verbose)-verbose/$(dotout)-dotout

default: $(buildprefix)/zebu

#ARGS += -v
#ARGS += --verbose

#ARGS += -l
#ARGS += --minimize-lexer

#ARGS += --template=really-just-tables
#ARGS += --template=just-tables

#ARGS += --template=readline-debug
#ARGS += --template=readline
#ARGS += --template=readline-with-driver-debug
ARGS += --template=readline-with-driver

#ARGS += --template=fileio-debug
#ARGS += --template=fileio

#ARGS += -i ./-examples/classic/classic.zb -o ./-examples/classic/classic
#ARGS += -i ./-examples/sandbox/sandbox.zb -o ./-examples/sandbox/sandbox

#ARGS += -i ./-examples/math/math.zb -o ./-examples/math/math
#ARGS += -i ./-examples/math2/math.zb -o ./-examples/math2/math

#ARGS += -i ./-examples/maia/maia.zb -o ./-examples/maia/maia
#ARGS += -i ./-examples/json/json.zb -o ./-examples/json/json
#ARGS += -i ./-examples/expressions/expressions.zb -o ./-examples/expressions/expressions
#ARGS += -i ./-examples/expressions2/expressions.zb -o ./-examples/expressions2/output
#ARGS += -i ./-examples/explode/explode.zb -o ./-examples/explode/explode
#ARGS += -i ./-examples/gegex/gegex.zb -o ./-examples/gegex/output
#ARGS += -i ./-examples/hard/hard.zb -o ./-examples/hard/output

ARGS += -i ./-examples/C/C.zb -o ./-examples/C/C

#ARGS += -i ./-examples/lisp/lisp.zb -o ./-examples/lisp/lisp

#ARGS += -i ./-examples/iloc/iloc1.zb -o ./-examples/iloc/iloc1
#ARGS += -i ./-examples/iloc/iloc2.zb -o ./-examples/iloc/iloc2
#ARGS += -i ./-examples/iloc/iloc3.zb -o ./-examples/iloc/iloc3

#ARGS += -i ./-examples/xml/xml.zb -o ./-examples/xml/xml

#ARGS += -i ./-examples/csv/csv.zb -o ./-examples/csv/csv

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

srcs += ./out/escaped/really_just_tables_source.c ./out/escaped/really_just_tables_header.c
srcs += ./out/escaped/just_tables_source.c        ./out/escaped/just_tables_header.c

#srcs += ./out/escaped/buffer_driven_source.c      ./out/escaped/buffer_driven_header.c

srcs += ./out/escaped/readline_source.c           ./out/escaped/readline_header.c
srcs += ./out/escaped/readline_debug_source.c     ./out/escaped/readline_debug_header.c
srcs += ./out/escaped/readline_with_driver_source.c       ./out/escaped/readline_with_driver_header.c
srcs += ./out/escaped/readline_with_driver_debug_source.c ./out/escaped/readline_with_driver_debug_header.c

srcs += ./out/escaped/fileio_source.c             ./out/escaped/fileio_header.c
srcs += ./out/escaped/fileio_debug_source.c       ./out/escaped/fileio_debug_header.c
#srcs += ./out/escaped/fileio_passfail_source.c    ./out/escaped/fileio_passfail_header.c
#srcs += ./out/escaped/fileio_graphviz_source.c    ./out/escaped/fileio_graphviz_header.c

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
















