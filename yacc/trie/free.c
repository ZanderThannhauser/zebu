
#include <debug.h>

#include <yacc/reductioninfo/free.h>

#include <yacc/structinfo/free.h>

#include "struct.h"
#include "free.h"

void free_trie(struct trie* this)
{
	ENTER;
	
	free_reductioninfo(this->reductioninfo);
	
	free_structinfo(this->structinfo);
	
	free_string(this->reduce_as);
	
	for (unsigned i = 0, n = this->transitions.n; i < n; i++)
	{
		struct trie_transition* ele = this->transitions.data[i];
		
		free_trie(ele->to);
		
		free(ele);
	}
	
	for (unsigned i = 0, n = this->grammar_transitions.n; i < n; i++)
	{
		struct trie_grammar_transition* ele = this->grammar_transitions.data[i];
		
		free_string(ele->grammar);
		
		free_trie(ele->to);
		
		free(ele);
	}
	
	free(this->transitions.data);
	free(this->grammar_transitions.data);
	
	EXIT;
}


