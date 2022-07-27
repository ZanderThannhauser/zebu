
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_tokenizer(struct tokenizer* this)
{
	ENTER;
	
	free(this->tokenchars.chars);
	free(this);
	
	EXIT;
}

