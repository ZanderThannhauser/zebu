
#include <sys/mman.h>

/*#include <valgrind/memcheck.h>*/

#include <debug.h>

/*#include <enums/error.h>*/

/*#include <defines/argv0.h>*/

#include <memory/smalloc.h>

/*#include "defines/INITIAL_MMAP_LENGTH.h"*/

/*#include "header.h"*/
/*#include "footer.h"*/
#include "struct.h"
#include "new.h"

struct memory_arena* new_memory_arena()
{
	struct memory_arena* this = smalloc(sizeof(*this));
	
	this->free_list.head = NULL;
	this->free_list.tail = NULL;
	
	this->mmaps.data = NULL;
	this->mmaps.cap = 0;
	this->mmaps.n = 0;
	
	return this;
}












