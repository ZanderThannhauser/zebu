
#include <debug.h>

#include <avl/tree_t.h>

#ifdef VERBOSE
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <misc/default_sighandler.h>
#endif

#include "struct.h"
#include "print_source.h"

void dyntable_print_source(struct dyntable* this, const char* prefix, FILE* stream)
{
	ENTER;
	
	#ifdef VERBOSE
	void handler(int _)
	{
		char ptr[100] = {};
		
		size_t len = snprintf(ptr, 100, "\e[K" "zebu: writing %s table ...\r", this->name);
		
		if (write(1, ptr, len) != len)
		{
			abort();
		}
	}
	
	signal(SIGALRM, handler);
	#endif
	
	fprintf(stream, "const unsigned %s_%s[%u][%u] = {\n", prefix, this->name, this->width + 1, this->height + 1);
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct dyntable_node* ele = node->item;
		
		fprintf(stream, "\t[%u][%u] = %u,\n", ele->x, ele->y, ele->v);
	}
	
	fprintf(stream, "};\n");
	
	#ifdef VERBOSE
	signal(SIGALRM, default_sighandler);
	#endif
	
	EXIT;
}







