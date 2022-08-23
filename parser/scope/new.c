
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
	struct memory_arena* arena,
	struct memory_arena* grammar_arena,
	struct avl_tree_t* grammar)
{
	ENTER;
	
	struct scope* this = arena_malloc(arena, sizeof(*this));
	
	this->grammar = grammar;
	this->grammar_arena = grammar_arena;
	
	this->prefix.chars = NULL;
	this->prefix.n = 0;
	this->prefix.cap = 0;
	
	this->arena = arena;
	
	this->layer = NULL;
	
	scope_push(this);
	
	EXIT;
	return this;
}












