
CPPFLAGS += -D _GNU_SOURCE
CPPFLAGS += -I .

CFLAGS += -Wall -Werror -Wfatal-errors

platform ?= linux

ifeq ($(platform), linux)
CC = gcc
CPPFLAGS += -D LINUX_PLATFORM
else ifeq ($(platform), windows)
CC = x86_64-w64-mingw32-gcc
CPPFLAGS += -D WINDOWS_PLATFORM
CPPFLAGS += -D __USE_MINGW_ANSI_STDIO=1
SUFFIX = .exe
else
$(error "invalid platform!");
endif

buildtype ?= release

ifeq ($(buildtype), release)
CPPFLAGS += -D RELEASE

CFLAGS += -O2
CFLAGS += -flto

LDFLAGS += -flto=auto
#LDFLAGS += -static

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

buildprefix = bin/$(platform)-platform/$(buildtype)-build/$(verbose)-verbose/$(dotout)-dotout
depprefix   = dep/$(platform)-platform/$(buildtype)-build/$(verbose)-verbose/$(dotout)-dotout

default: $(buildprefix)/zebu$(SUFFIX)

#ARGS += -v
ARGS += --verbose

#ARGS += -m
#ARGS += --minimize-lexer

#ARGS += -M
#ARGS += --make-dependencies

#ARGS += -F /tmp/out.d

#ARGS += --template=really-just-tables
#ARGS += --template=just-tables

#ARGS += --template=charbuffer
#ARGS += --template=piecewise-charbuffer

#ARGS += --template=readline
#ARGS += --template=readline-with-driver

ARGS += --template=fileio
#ARGS += --template=fileio-with-driver

#ARGS += --program-name bash

#ARGS += --custom-template=./out/-templates/really_just_tables
#ARGS += --custom-source-template=./out/-templates/really_just_tables.c
#ARGS += --custom-header-template=./out/-templates/really_just_tables.h

#ARGS += -i ./-examples/classic/classic.zb -o /tmp/classic
#ARGS += -i ./-examples/sandbox/sandbox.zb -o /tmp/sandbox

#ARGS += -i ./-examples/math/math.zb -o /tmp/math
#ARGS += -i ./-examples/math2/math.zb -o /tmp/math

#ARGS += -i ./-examples/maia/maia.zb -o /tmp/maia
ARGS += -i ./-examples/json/json.zb -o /tmp/json
#ARGS += -i ./-examples/expressions/expressions.zb -o /tmp/expressions
#ARGS += -i ./-examples/expressions2/expressions.zb -o /tmp/output
#ARGS += -i ./-examples/explode/explode.zb -o /tmp/explode
#ARGS += -i ./-examples/gegex/gegex.zb -o /tmp/gegex
#ARGS += -i ./-examples/hard/hard.zb -o /tmp/hard

#ARGS += -i ./-examples/C/C.zb -o /tmp/C

#ARGS += -i ./-examples/lisp/parser.zb -o /tmp/parser
#ARGS += -i ./-examples/carrs-lisp/parser.zb -o /tmp/carr

#ARGS += -i ./-examples/iloc/iloc1.zb -o /tmp/iloc1
#ARGS += -i ./-examples/iloc/iloc2.zb -o /tmp/iloc2
#ARGS += -i ./-examples/iloc/iloc3.zb -o /tmp/iloc3

#ARGS += -i ./-examples/xml/xml.zb -o /tmp/xml

#ARGS += -i ./-examples/csv/csv.zb -o /tmp/csv

#ARGS += -i ./-examples/zebu/zebu.zb -o /tmp/zebu

run: $(buildprefix)/zebu$(SUFFIX)
	$< $(ARGS)

winerun: $(buildprefix)/zebu$(SUFFIX)
	wine $< $(ARGS)

valrun: $(buildprefix)/zebu$(SUFFIX)
	valgrind $< $(ARGS)

valrun-stop: $(buildprefix)/zebu$(SUFFIX)
	valgrind --gen-suppressions=yes -- $< ${ARGS}

valrun-leak: $(buildprefix)/zebu$(SUFFIX)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -- $< ${ARGS}

tracerun: $(buildprefix)/zebu$(SUFFIX)
	strace $< $(ARGS)

PREFIX ?= ~/bin

install: $(buildprefix)/zebu
	@ mkdir -vp $(PREFIX)
	@ cp -vau $(buildprefix)/zebu $(PREFIX)/zebu

.PRECIOUS: %/

%/:
	@ mkdir -p $@

srclist.mk:
	@ echo "searching for source files..."
	@ find -name '*.c' -! -path '*/-*' | sort -V | sed 's/^/srcs += /' > $@

ifneq "$(MAKECMDGOALS)" "clean"
include srclist.mk

srcs += ./out/escaped/really_just_tables_source.c ./out/escaped/really_just_tables_header.c
srcs += ./out/escaped/just_tables_source.c        ./out/escaped/just_tables_header.c

srcs += ./out/escaped/charbuffer_source.c      ./out/escaped/charbuffer_header.c
srcs += ./out/escaped/piecewise_charbuffer_source.c      ./out/escaped/piecewise_charbuffer_header.c

srcs += ./out/escaped/readline_source.c           ./out/escaped/readline_header.c
srcs += ./out/escaped/readline_with_driver_source.c       ./out/escaped/readline_with_driver_header.c

srcs += ./out/escaped/fileio_with_driver_source.c       ./out/escaped/fileio_with_driver_header.c
#srcs += ./out/escaped/fileio_passfail_source.c    ./out/escaped/fileio_passfail_header.c
#srcs += ./out/escaped/fileio_graphviz_source.c    ./out/escaped/fileio_graphviz_header.c
endif

objs := $(patsubst %.c,$(buildprefix)/%.o,$(srcs))
objs := $(patsubst %.S,$(buildprefix)/%.o,$(objs))

deps := $(patsubst %.c,$(depprefix)/%.d,$(srcs))
deps := $(patsubst %.S,$(depprefix)/%.d,$(deps))

$(buildprefix)/zebu$(SUFFIX): $(objs)
	@ echo "linking $@"
	@ $(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@

$(buildprefix)/%.o $(depprefix)/%.d: %.c | $(buildprefix)/%/ $(depprefix)/%/
	@ echo "compiling $<"
	@ $(CC) -c $(CPPFLAGS) $(CFLAGS) $< -MMD -o $(buildprefix)/$*.o -MF $(depprefix)/$*.d $(ON_ERROR)

bin/escape: ./-escape.c | bin/
	@ echo "compiling $<"
	@ gcc -Wall -Werror ./$< -o $@

.PRECIOUS: ./out/escaped/%_source.c
.PRECIOUS: ./out/escaped/%_header.c

./out/escaped/%_source.c: bin/escape ./out/-templates/%.c | bin/
	@ echo "escaping $*"
	@ $^ -v $*_source -o $@

./out/escaped/%_header.c: bin/escape ./out/-templates/%.h | bin/
	@ echo "escaping $*"
	@ $^ -v $*_header -o $@

dot/%.png: dot/%.dot
	dot -Tpng < $< > $@

clean:
	for l in $$(cat .gitignore); do rm -rvf $$l; done

ifneq "$(MAKECMDGOALS)" "clean"
include $(deps)
endif
















