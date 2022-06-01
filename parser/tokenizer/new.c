
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

int new_tokenizer(struct tokenizer** out, int fd)
{
	int error = 0;
	ENTER;
	
	struct tokenizer* this;
	
	if (!error)
		error = smalloc((void**) &this, sizeof(*this));
	
	if (!error)
	{
		this->fd = fd;
		
		this->buffer.i = 0;
		this->buffer.n = 0;
		
		this->tokenchars.chars = NULL;
		this->tokenchars.n = 0;
		this->tokenchars.cap = 0;
		
		*out = this;
	}
	
	EXIT;
	return error;
}

