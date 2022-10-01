
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <enums/error.h>

#include <cmdln/output_path.h>
#include <cmdln/make_dependencies_file.h>

#include "struct.h"
#include "print_dependencies.h"

void pragma_once_print_dependencies(struct pragma_once* this)
{
	ENTER;
	
	dpvs(make_dependencies_file);
	
	FILE* stream = fopen(make_dependencies_file, "w");
	
	if (!stream)
	{
		fprintf(stderr, "zebu: fopen(\"%s\"): %s\n", make_dependencies_file, strerror(errno));
		exit(e_syscall_failed);
	}
	
	fprintf(stream, "%s.c:", output_path);
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		dpvs(node->item);
		fprintf(stream, " \\\n\t%s", (char*) node->item);
	}
	
	fprintf(stream, "\n");
	
	fclose(stream);
	
	EXIT;
}




