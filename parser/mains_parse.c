
#include <avl/new.h>

#include <debug.h>

#include <memory/sstrdup.h>
#include <memory/arena/new.h>
#include <memory/arena/free.h>

#include "pragma_once/new.h"
#include "pragma_once/free.h"

#include "recursive_parse.h"
#include "mains_parse.h"

int mains_parse(
	struct avl_tree_t* grammar,
	const char* path,
	struct lex* lex)
{
	int error = 0;
	char* dup = NULL;
	struct avl_tree_t* fragments = NULL;
	struct pragma_once* pragma_once = NULL;
	struct memory_arena* token_scratchpad = NULL;
	ENTER;
	
	error = 0
		?: sstrdup(&dup, path)
		?: new_pragma_once(&pragma_once)
		?: new_memory_arena(&token_scratchpad)
		?: new_avl_tree(&fragments, NULL, NULL)
		?: recursive_parse(
			/* grammar: */ grammar,
			/* fragments: */ fragments,
			/* pragma_once: */ pragma_once,
			/* token_scratchpad: */ token_scratchpad,
			/* absolute_dirfd: */ AT_FDCWD,
			/* relative_dirfd: */ AT_FDCWD,
			/* path: */ dup,
			/* lex: */ lex
		);
	
	TODO;
	
	free(dup);
	free_memory_arena(token_scratchpad);
	
	#if 0
	free_pragma_once(pragma_once);
	avl_free_tree(fragments);
	#endif
	
	EXIT;
	return error;
}
















