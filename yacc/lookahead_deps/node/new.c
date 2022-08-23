
#include <stdlib.h>
#include <debug.h>

#include <arena/malloc.h>

#include <set/of_gegexes/new.h>
#include <set/of_gegexes/add.h>

#include "struct.h"
#include "new.h"

struct lookahead_deps_node* new_lookahead_deps_node(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct gegex* a,
	struct gegex* b)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct lookahead_deps_node* this = arena_malloc(arena, sizeof(*this));
	#else
	struct lookahead_deps_node* this = malloc(sizeof(*this));
	#endif
	
	this->a = a;
	
	#ifdef WITH_ARENAS
	this->b = new_gegexset(arena);
	#else
	this->b = new_gegexset();
	#endif
	
	gegexset_add(this->b, b);
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	#endif
	
	EXIT;
	return this;
}

