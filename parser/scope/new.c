
#include <debug.h>

/*#include <avl/new.h>*/

#include <memory/smalloc.h>

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

struct scope* new_scope(struct avl_tree_t* grammar)
{
	ENTER;
	
	struct scope* this = smalloc(sizeof(*this));
	
	this->grammar = grammar;
	
	this->prefix.chars = NULL;
	this->prefix.n = 0;
	this->prefix.cap = 0;
	
	this->layer = NULL;
	
	scope_push(this);
	
	EXIT;
	return this;
}












