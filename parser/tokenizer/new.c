
#include <debug.h>

#include "struct.h"
#include "new.h"

struct tokenizer* new_tokenizer(int fd)
{
	ENTER;
	
	struct tokenizer* this = malloc(sizeof(*this));
	
	assert(this);
	
	this->fd = fd;
	
	this->buffer.i = 0;
	this->buffer.n = 0;
	
	this->tokenchars.chars = NULL;
	this->tokenchars.n = 0;
	this->tokenchars.cap = 0;
	
	EXIT;
	return this;
}

