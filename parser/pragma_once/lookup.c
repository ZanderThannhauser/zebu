
#include <avl/avl.h>

#include <debug.h>

#include <memory/smemdup.h>

#include "struct.h"
#include "node.h"
#include "lookup.h"

int pragma_once_lookup(
	struct pragma_once* this,
	bool* out,
	int fd)
{
	int error = 0;
	struct stat statbuf;
	ENTER;
	
	if (fstat(fd, &statbuf) < 0)
	{
		TODO;
		error = 1;
	}
	
	dpvo(statbuf.st_dev);
	dpvx(statbuf.st_ino);
	
	struct pragma_once_node node = {
		.dev = statbuf.st_dev,
		.ino = statbuf.st_ino,
	};
		
	if (!error && (*out = !avl_search(&this->tree, &node)))
	{
		struct pragma_once_node* new = NULL;
		
		error = smemdup((void**) &new, &node, sizeof(node));
		
		if (!error && !avl_insert(&this->tree, new))
		{
			TODO;
			error = e_out_of_memory;
			free(new);
		}
	}
	
	EXIT;
	return error;
}
















