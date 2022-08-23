
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>

/*#include <avl/new.h>*/

/*#include <avl/init_tree.h>*/

/*#include "named/charset/compare.h"*/
/*#include "named/charset/free.h"*/
/*#include "named/token/compare.h"*/
/*#include "named/token/free.h"*/
/*#include "named/grammar/compare.h"*/
/*#include "named/grammar/free.h"*/

#include "struct.h"
#include "new.h"
#include "push.h"

struct scope* new_scope(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	struct memory_arena* grammar_arena,
	#endif
	struct avl_tree_t* grammar)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct scope* this = arena_malloc(arena, sizeof(*this));
	#else
	struct scope* this = malloc(sizeof(*this));
	#endif
	
	this->grammar = grammar;
	
	this->prefix.chars = NULL;
	this->prefix.n = 0;
	this->prefix.cap = 0;
	
	#ifdef WITH_ARENAS
	this->arena = arena;
	this->grammar_arena = grammar_arena;
	#endif
	
	this->layer = NULL;
	
	scope_push(this);
	
	EXIT;
	return this;
}












