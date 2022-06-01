
#include <stdlib.h>

struct arena_header;

struct memory_arena
{
	struct {
		struct {
			void *start;
			size_t size;
		}* data;
		size_t n, cap;
	} mmaps;
	
	struct {
		struct memory_arena_header *head;
		struct memory_arena_header *tail;
	} free_list;
};

