
#include <debug.h>

#include <arena/malloc.h>

#include <set/of_gegexes/new.h>
#include <set/of_gegexes/add.h>

#include "struct.h"
#include "new.h"

struct lookahead_deps_node* new_lookahead_deps_node(
	struct memory_arena* arena,
	struct gegex* a,
	struct gegex* b)
{
	ENTER;
	
	struct lookahead_deps_node* this = arena_malloc(arena, sizeof(*this));
	
	this->a = a;
	
	this->b = new_gegexset(arena);
	
	gegexset_add(this->b, b);
	
	this->arena = arena;
	
	EXIT;
	return this;
}

