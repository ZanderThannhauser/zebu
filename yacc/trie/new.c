
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct trie* new_trie()
{
	ENTER;
	
	struct trie* this = smalloc(sizeof(*this));
	
	this->reductioninfo = NULL;
	this->structinfo = NULL;
	this->reduce_as = NULL;
	this->grammar = NULL;
	
	this->transitions.data = NULL;
	this->transitions.n = 0;
	this->transitions.cap = 0;
	
	this->grammars.data = NULL;
	this->grammars.n = 0;
	this->grammars.cap = 0;
	
	EXIT;
	return this;
}

