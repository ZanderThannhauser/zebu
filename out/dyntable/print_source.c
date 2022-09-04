
#include <debug.h>

#include <avl/tree_t.h>

#ifdef VERBOSE
#include <unistd.h>
#include <stdlib.h>
#include <cmdln/verbose.h>
#include <signal.h>
#include <misc/default_sighandler.h>
#endif

#include "struct.h"
#include "print_source.h"

void dyntable_print_source(
	struct dyntable* this,
	const char* prefix,
	FILE* source,
	FILE* header)
{
	ENTER;
	
	TODO;
	#if 0
	dpvs(this->name);
	
	#ifdef VERBOSE
	void handler(int _)
	{
		char ptr[100] = {};
		
		size_t len = snprintf(ptr, 100, "\e[K" "zebu: write %s table ...\r", this->name);
		
		if (write(1, ptr, len) != len)
		{
			abort();
		}
	}
	
	if (verbose)
		signal(SIGALRM, handler);
	#endif
	
	fprintf(header, "extern const unsigned %s_%s[%u][%u];\n",
		prefix, this->name, this->width + 1, this->height + 1);
	
	fprintf(source, "const unsigned %s_%s[%u][%u] = {\n",
		prefix, this->name, this->width + 1, this->height + 1);
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct dyntable_node* ele = node->item;
		
		fprintf(source, "\t[%u][%u] = %u,\n", ele->x, ele->y, ele->v);
	}
	
	fprintf(source, "};\n");
	
	#ifdef VERBOSE
	if (verbose)
		signal(SIGALRM, default_sighandler);
	#endif
	#endif
	
	EXIT;
}







