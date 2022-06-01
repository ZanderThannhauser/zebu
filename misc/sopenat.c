
#include <debug.h>

#include "sopenat.h"

int sopenat(int* out, int dirfd, const char* path, int flags)
{
	int error = 0;
	ENTER;
	
	dpv(dirfd);
	dpvs(path);
	
	if ((*out = openat(dirfd, path, flags)) < 0)
	{
		fprintf(stderr, "%s: open(): %m\n", argv0),
		error = e_syscall_failed;
	}
	
	#ifdef DEBUGGING
	if (!error)
	{
		dpv(*out);
	}
	#endif
	
	EXIT;
	return error;
}

