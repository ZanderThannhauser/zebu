
#include <debug.h>

#include "malloc.h"

void* mmap_malloc(struct memory_arena* this, size_t size)
{
	ENTER;
	
	dpv(size);
	
	void* ptr;
	
	if ((ptr = mmap(
		/* addr:   */  NULL,
		/* length: */  size,
		/* prot:   */  PROT_READ | PROT_WRITE,
		/* flags:  */  MAP_ANONYMOUS | MAP_PRIVATE,
		/* fd:     */ -1,
		/* offset: */  0)) == MAP_FAILED)
	{
		fprintf(stderr, "%s: mmap(): %m\n", argv0);
		exit(e_syscall_failed);
	}
	
	dpv(ptr);
	
	EXIT;
	return ptr;
}

