
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

#include <debug.h>

/*#include <defines/argv0.h>*/

#include <enums/error.h>

#include <avl/search.h>
#include <avl/insert.h>

#include "node/struct.h"
#include "node/new.h"
#include "struct.h"
#include "lookup.h"

bool pragma_once_lookup(struct pragma_once* this, int fd)
{
	struct stat statbuf;
	ENTER;
	
	if (fstat(fd, &statbuf) < 0)
	{
		fprintf(stderr, "zebu: fstat(): %m\n");
		exit(e_syscall_failed);
	}
	
	dpvo(statbuf.st_dev);
	dpvx(statbuf.st_ino);
	
	bool first_time = !avl_search(this->tree, &(struct pragma_once_node) {
		.dev = statbuf.st_dev,
		.ino = statbuf.st_ino,
	});
	
	dpvb(first_time);
	
	if (first_time)
	{
		avl_insert(this->tree, new_pragma_once_node(statbuf.st_dev, statbuf.st_ino));
	}
	
	EXIT;
	return first_time;
}


























