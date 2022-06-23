
#include <avl/avl.h>
#include <avl/new.h>

#include <debug.h>

#include <memory/sstrdup.h>
#include <memory/arena/new.h>
#include <memory/arena/free.h>

#include "scope/new.h"

#include "options/new.h"

#include "pragma_once/new.h"
#include "pragma_once/free.h"

#include "recursive_parse.h"
#include "mains_parse.h"

struct avl_tree_t* mains_parse(const char* path, struct lex* lex)
{
	ENTER;
	
	struct scope* scope = new_scope();
	
	struct options* options = new_options();
	
	char* dup = sstrdup(path);
	
	struct pragma_once* pragma_once = new_pragma_once();
	
	struct memory_arena* scratchpad = new_memory_arena();
	
	recursive_parse(
		/* options: */ options,
		/* scope: */ scope,
		/* pragma_once: */ pragma_once,
		/* scratchpad: */ scratchpad,
		/* absolute_dirfd: */ AT_FDCWD,
		/* relative_dirfd: */ AT_FDCWD,
		/* path: */ dup,
		/* lex: */ lex
	);
	
	TODO;
	#if 0
	free(dup);
	
	free_memory_arena(scratchpad);
	
	free_pragma_once(pragma_once);
	
	// lookup options->start_rule in grammar tree,
	// keep a reference to return
	TODO;
	
	free_scope(scope);
	#endif
	
	EXIT;
	// return reference to start rule's grammar
	TODO;
}
















