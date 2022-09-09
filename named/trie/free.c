
#include <stdlib.h>

#include <debug.h>

#include <string/free.h>

#include <yacc/trie/free.h>

#include "struct.h"
#include "free.h"

void free_named_trie(void* ptr)
{
	struct named_trie* this = ptr;
	
	free_string(this->name);
	
	free_trie(this->trie);
	
	free(this);
}

