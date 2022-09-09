
#include <debug.h>

#include <memory/smalloc.h>

#include <string/inc.h>

#include <yacc/structinfo/inc.h>

#include "struct.h"
#include "inc.h"
#include "new.h"

struct reductioninfo* new_reductioninfo(
	enum reductioninfo_kind kind,
	struct structinfo* structinfo, // could be NULL
	struct string* grammar,
	struct reductioninfo* prev)
{
	ENTER;
	
	struct reductioninfo* this = smalloc(sizeof(*this));
	
	this->kind = kind;
	
	this->structinfo = inc_structinfo(structinfo);
	
	this->grammar = inc_string(grammar);
	
	this->prev = inc_reductioninfo(prev);
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

