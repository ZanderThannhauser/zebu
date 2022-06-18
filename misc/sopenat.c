
#include <debug.h>

#include "sopenat.h"

int sopenat(int dirfd, const char* path, int flags)
{
	int fd = openat(dirfd, path, flags);
	
	if (fd < 0)
	{
		fprintf(stderr, "%s: open(): %m\n", argv0),
		exit(e_syscall_failed);
	}
	
	return fd;
}

