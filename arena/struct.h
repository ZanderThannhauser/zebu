
#include <stdlib.h>

struct memory_arena
{
	struct {
		struct mentry {
			void *start;
			size_t size;
		}* data;
		size_t n, cap;
	} mmaps;
	
	struct {
		struct memory_arena_header *head;
		struct memory_arena_header *tail;
	} free_list;
	
	void* (*malloc)(struct memory_arena* arena, size_t size);
	
	void* (*realloc)(struct memory_arena* arena, void* ptr, size_t newsize);
	
	bool (*resize)(struct memory_arena* arena, void* ptr, size_t oldsize, size_t newsize);
	
	void (*free)(struct memory_arena* arena, void* ptr);
	
	union
	{
		struct {
			
		} stdlib;
		
		struct {
			
		} mmap;
		
		struct {
			struct memory_arena* parent;
		} child;
	};
};



