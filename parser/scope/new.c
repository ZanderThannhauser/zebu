
#include <debug.h>

#include <memory/smalloc.h>

#include <avl/init_tree.h>

#include "named/charset/compare.h"
#include "named/charset/free.h"
#include "named/token/compare.h"
#include "named/token/free.h"
#include "named/grammar/compare.h"
#include "named/grammar/free.h"

#include "struct.h"
#include "new.h"
#include "push.h"

struct scope* new_scope()
{
	ENTER;
	
	struct scope* this = smalloc(sizeof(*this));
	
	avl_init_tree(&this->charsets, compare_named_charsets, free_named_charset);
	avl_init_tree(&this->tokens,   compare_named_tokens,   free_named_token);
	avl_init_tree(&this->grammar,  compare_named_grammar,  free_named_grammar);
	
	this->prefix.chars = NULL;
	this->prefix.n = 0;
	this->prefix.cap = 0;
	
	this->layer = NULL;
	
	scope_push(this);
	
	EXIT;
	return this;
}












