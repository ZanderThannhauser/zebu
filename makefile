
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

on_error ?= do_nothing

ifeq ($(on_error), do_nothing)
ON_ERROR =
else ifeq ($(on_error), open_editor)
ON_ERROR += || ($$EDITOR $<; false)
else
$(error "invalid on_error option!");
endif

buildprefix = gen/$(buildtype)-build

default: $(buildprefix)/zebu

ARGS += -v

#ARGS += -j

ARGS += --debug=yacc
#ARGS += --debug=lex

#ARGS += -i ./examples/classic/classic.zb -o ./examples/classic/output
#ARGS += -i ./examples/math/math.zb -o ./examples/math/output
#ARGS += -i ./examples/maia/maia.zb -o ./examples/maia/output
#ARGS += -i ./examples/json/json.zb -o ./examples/json/output
#ARGS += -i ./examples/C-expressions/C.zb -o ./examples/C-expressions/output
ARGS += -i ./examples/explode/explode.zb -o ./examples/explode/output
ARGS += -i ./examples/gegex/gegex.zb -o ./examples/gegex/output

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

.PRECIOUS: %/

%/:
	@ mkdir -p $@

gen/srclist.mk: | gen/%/
	@ echo "searching for source files..."
	@ find -name '*.c' -! -path './examples/*' | sort -Vr | sed 's/^/srcs += /' > $@

ifneq "$(MAKECMDGOALS)" "clean"
include gen/srclist.mk
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

dot/%.png: dot/%.dot
	dot -Tpng < $< > $@

clean:
	for l in $$(cat .gitignore); do rm -rvf $$l; done

ifneq "$(MAKECMDGOALS)" "clean"
include $(deps)
endif
















