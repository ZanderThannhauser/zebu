
#include <stdlib.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <set/unsigned/inc.h>

#include <set/unsignedset/inc.h>

#include "struct.h"
#include "new.h"

struct build_tokenizer_node* new_build_tokenizer_node(
	struct unsignedset* token_ids,
	struct unsignedsetset* matches,
	struct lex_state* start)
{
	ENTER;
	
	struct build_tokenizer_node* this = smalloc(sizeof(*this));
	
	this->given = inc_unsignedset(token_ids);
	
	this->matches = inc_unsignedsetset(matches);
	
	this->start = start;
	
	EXIT;
	return this;
}

