
#include <debug.h>

#include <memory/smalloc.h>

#include <set/of_gegexes/new.h>
#include <set/of_gegexes/add.h>

#include "struct.h"
#include "new.h"

struct lookahead_deps_node* new_lookahead_deps_node(
	struct gegex* a,
	struct gegex* b)
{
	ENTER;
	
	struct lookahead_deps_node* this = smalloc(sizeof(*this));
	
	this->a = a;
	
	this->b = new_gegexset();
	
	gegexset_add(this->b, b);
	
	EXIT;
	return this;
}

