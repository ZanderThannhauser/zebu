
#include <assert.h>
#include <debug.h>

#include "header.h"
#include "footer.h"
#include "get_size.h"

size_t arena_get_size(void* ptr)
{
	assert(ptr);
	
	struct memory_arena_header* header = ptr - sizeof(*header);
	
	size_t block_size = header->size;
	
	size_t user_size = block_size - sizeof(*header) - sizeof(struct memory_arena_footer);
	
	return user_size;
}

