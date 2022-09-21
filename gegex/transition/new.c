
#include <debug.h>

#include <set/unsigned/inc.h>

#include <yacc/structinfo/inc.h>

#include "struct.h"
#include "new.h"

struct gegex_transition* new_gegex_transition(
	unsigned token,
	struct unsignedset* whitespace,
	struct structinfo* structinfo,
	struct gegex* to)
{
	ENTER;
	
	struct gegex_transition* this = smalloc(sizeof(*this));
	
	this->token = token;
	this->whitespace = inc_unsignedset(whitespace);
	this->structinfo = inc_structinfo(structinfo);
	this->to = to;
	
	EXIT;
	return this;
}

