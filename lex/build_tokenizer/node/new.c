
#include <debug.h>

/*#include <memory/smalloc.h>*/

#include <set/of_tokens/clone.h>

#include "struct.h"
#include "new.h"

struct build_tokenizer_node* new_build_tokenizer_node(
	struct tokenset* token_ids,  // needs to be cloned
	struct tokensetset* matches,
	struct lex_state* start)
{
	ENTER;
	
	TODO;
	#if 0
	struct build_tokenizer_node* this = smalloc(sizeof(*this));
	
	this->given = tokenset_clone(token_ids);
	
	this->matches = matches;
	
	this->start = start;
	
	EXIT;
	return this;
	#endif
}

