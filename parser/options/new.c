
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct options* new_options()
{
	struct options* this = smalloc(sizeof(*this));
	
	this->skip = NULL;
	this->token_skip = NULL;
	
	this->disambiguatations.head = NULL;
	this->disambiguatations.tail = NULL;
	
	return this;
}

