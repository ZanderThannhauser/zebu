
#include <avl/avl.h>
#include <avl/new.h>

#include <debug.h>

#include <memory/sstrdup.h>
/*#include <memory/arena/new.h>*/
/*#include <memory/arena/free.h>*/

/*#include "scope/new.h"*/

/*#include "options/new.h"*/

#include "pragma_once/new.h"
#include "pragma_once/free.h"

#include "resolve_grammar_names.h"
#include "recursive_parse.h"
#include "mains_parse.h"

void mains_parse(
	struct options* options,
	struct scope* scope,
	struct memory_arena* scratchpad,
	struct lex* lex,
	const char* path)
{
	ENTER;
	
	char* dup = sstrdup(path);
	
	struct pragma_once* pragma_once = new_pragma_once();
	
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
	
	free_pragma_once(pragma_once);
	
	free(dup);
	
	resolve_grammar_names(scope);
	
	EXIT;
	// return (options, scope, scratchpad);
}
















