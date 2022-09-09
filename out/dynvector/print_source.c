
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

void dynvector_print_source(
	struct dynvector* this,
	const char* prefix,
	FILE* stream)
{
	ENTER;
	
	dpvs(this->name);
	
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
	
	fprintf(stream, "const unsigned %s_%s[%u] = {\n", prefix, this->name, this->length + 1);
	
	for (struct avl_node_t* node = this->list->head; node; node = node->next)
	{
		struct dynvector_node* ele = node->item;
		
		fprintf(stream, "\t[%u] = %u,\n", ele->i, ele->v);
	}
	
	fprintf(stream, "};\n");
	
	#ifdef VERBOSE
	signal(SIGALRM, default_sighandler);
	#endif
	
	EXIT;
}














