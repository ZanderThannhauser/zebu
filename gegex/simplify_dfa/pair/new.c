
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "new.h"

struct gegex_pair* new_gegex_pair(
	struct gegex* a, struct gegex* b
) {
	ENTER;
	
	struct gegex_pair* this = smalloc(sizeof(*this));
	
	assert(a < b);
	
	this->a = a;
	this->b = b;
	
	EXIT;
	return this;
}
