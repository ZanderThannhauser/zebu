

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

#include <debug.h>

#include <enums/error.h>
#include "struct.h"
#include "read_char.h"

void read_char(struct tokenizer* this)
{
	ssize_t rretval;
	
	if (this->buffer.i < this->buffer.n)
	{
		this->c = this->buffer.data[this->buffer.i++];
	}
	else if ((rretval = read(this->fd, this->buffer.data, sizeof(this->buffer.data))) < 0)
	{
		fprintf(stderr, "zebu: read(): %s\n", strerror(errno)),
		exit(e_syscall_failed);
	}
	else if (!rretval)
	{
		this->c = '\0';
	}
	else
	{
		this->buffer.i = 0;
		this->buffer.n = rretval;
		this->c = this->buffer.data[this->buffer.i++];
	}
	
	#ifdef DEBUGGING
	dpvc(this->c);
	#endif
}

