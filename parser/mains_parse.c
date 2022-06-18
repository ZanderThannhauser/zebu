
#include <avl/avl.h>
#include <avl/new.h>

#include <debug.h>

#include <memory/sstrdup.h>
#include <memory/arena/new.h>
#include <memory/arena/free.h>

#include "options/new.h"

#include "fragment/compare.h"
#include "fragment/free.h"

#include "pragma_once/new.h"
#include "pragma_once/free.h"

#include "recursive_parse.h"
#include "mains_parse.h"

struct avl_tree_t* mains_parse(const char* path, struct lex* lex)
{
	ENTER;
	
	struct avl_tree_t* grammar = new_avl_tree(NULL, NULL);
	
	struct options* options = new_options();
	
	struct avl_tree_t* fragments = new_avl_tree(compare_fragments, free_fragment);
	
	char* dup = sstrdup(path);
	
	struct pragma_once* pragma_once = new_pragma_once();
	
	struct memory_arena* scratchpad = new_memory_arena();
	
	recursive_parse(
		/* grammar: */ grammar,
		/* options: */ options,
		/* fragments: */ fragments,
		/* pragma_once: */ pragma_once,
		/* token_scratchpad: */ scratchpad,
		/* absolute_dirfd: */ AT_FDCWD,
		/* relative_dirfd: */ AT_FDCWD,
		/* path: */ dup,
		/* lex: */ lex
	);
	
	free(dup);
	
	free_memory_arena(scratchpad);
	
	free_pragma_once(pragma_once);
	
	avl_free_tree(fragments);
	
	EXIT;
	return grammar;
}
















