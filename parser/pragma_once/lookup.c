
#include <avl/safe_insert.h>

#include <debug.h>

#include <memory/smemdup.h>

#include "struct.h"
#include "node.h"
#include "lookup.h"

bool pragma_once_lookup(struct pragma_once* this, int fd)
{
	struct stat statbuf;
	ENTER;
	
	if (fstat(fd, &statbuf) < 0)
	{
		fprintf(stderr, "%s: fstat(): %m\n", argv0);
		exit(e_syscall_failed);
	}
	
	dpvo(statbuf.st_dev);
	dpvx(statbuf.st_ino);
	
	struct pragma_once_node node = {
		.dev = statbuf.st_dev,
		.ino = statbuf.st_ino,
	};
	
	bool first_time;
	
	if ((first_time = !avl_search(&this->tree, &node)))
	{
		struct pragma_once_node* new = smemdup(&node, sizeof(node));
		
		safe_avl_insert(&this->tree, new);
	}
	
	EXIT;
	return first_time;
}



























