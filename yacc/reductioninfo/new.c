
#include <debug.h>

#include <set/string/inc.h>

#include "struct.h"
#include "inc.h"
#include "new.h"

struct reductioninfo* new_reductioninfo(
	enum reductioninfo_kind kind,
	struct stringset* tags,
	struct string* grammar,
	struct reductioninfo* prev)
{
	ENTER;
	
	struct reductioninfo* this = smalloc(sizeof(*this));
	
	this->kind = kind;
	
	this->tags = inc_stringset(tags);
	
	this->grammar = inc_string(grammar);
	
	this->prev = inc_reductioninfo(prev);
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

