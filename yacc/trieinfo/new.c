
#include <debug.h>

#include "struct.h"

#include "new.h"

struct trieinfo* new_trieinfo(
	char* name, // you're giving this to me
	struct trie* start
) {
	ENTER;
	
	struct trieinfo* this = smalloc(sizeof(*this));
	
	this->name = name;
	this->start = start;
	
	EXIT;
	return this;
}

