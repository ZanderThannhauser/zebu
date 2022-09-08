
#include <debug.h>

#include <stdio.h>
#include <fcntl.h>

#include <stdlib.h>

#include <enums/error.h>

#include "sopenat.h"

int sopenat(int dirfd, const char* path, int flags)
{
	int fd = openat(dirfd, path, flags);
	
	if (fd < 0)
	{
		fprintf(stderr, "zebu: open(): %m\n"),
		exit(e_syscall_failed);
	}
	
	return fd;
}

