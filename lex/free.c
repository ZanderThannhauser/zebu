
#ifdef WITHOUT_ARENAS

#include <stdlib.h>
#include <debug.h>

#include <set/of_tokens/free.h>

#include <avl/free_tree.h>

#include "struct.h"
#include "free.h"

void free_lex(struct lex* this)
{
	ENTER;
	
	free_tokenset(this->disambiguations.literal_ids);
	
	free_tokenset(this->disambiguations.regex_ids);
	
	avl_free_tree(this->dfa_to_id);
	
	avl_free_tree(this->dfa_from_id);
	
	avl_free_tree(this->tokenizer.cache);
	
	free(this);
	
	EXIT;
}

#endif
