
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct pragma_once_node* new_pragma_once_node(dev_t dev, ino_t ino)
{
	ENTER;
	
	struct pragma_once_node* this = smalloc(sizeof(*this));
	
	this->dev = dev;
	this->ino = ino;
	
	dpv(this->dev);
	dpv(this->ino);
	
	EXIT;
	return this;
}

