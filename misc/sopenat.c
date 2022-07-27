
#include <debug.h>

#include <stdio.h>
#include <fcntl.h>

#include <defines/argv0.h>

#include <stdlib.h>

#include <enums/error.h>

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

