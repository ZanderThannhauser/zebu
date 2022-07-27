
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#include "output.h"

int main()
{
	int fd = open("input.txt", O_RDONLY);
	
	if (fd < 0)
	{
		fprintf(stderr, "open(input.txt): %m\n"),
		exit(1);
	}
	
	struct zebu_state* parser = new_zebu_state();
	
	unsigned char buffer[1024];
	ssize_t readval;
	
	while ((readval = read(fd, buffer, sizeof(buffer))) > 0)
		zebu_parse(parser, buffer, readval);
	
	if (readval < 0)
	{
		fprintf(stderr, "read(input.txt): %m\n"),
		exit(1);
	}
	
	zebu_parse_EOF(parser);
	
	free_zebu_state(parser);
	
	close(fd);
	
	return 0;
}

