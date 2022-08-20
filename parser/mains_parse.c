
#include <stdlib.h>

#include <assert.h>

#include <fcntl.h>

#include <debug.h>

/*#include <avl/avl.h>*/
/*#include <avl/new.h>*/

#include <memory/sstrdup.h>

#include <misc/sopen.h>
#include <misc/sopenat.h>
#include <misc/break_path.h>

/*#include <memory/arena/new.h>*/
/*#include <memory/arena/free.h>*/

/*#include <set/of_strs/add.h>*/

/*#include "options/struct.h"*/

#include "scope/new.h"
#include "scope/free.h"

#include "pragma_once/new.h"
#include "pragma_once/free.h"

#include "resolve_grammar_names.h"
#include "recursive_parse.h"
#include "mains_parse.h"

void mains_parse(
	struct options* options,
	struct avl_tree_t* grammar,
	struct memory_arena* scratchpad,
	struct lex* lex,
	const char* path)
{
	ENTER;
	
	dpvs(path);
	
	struct br_rettype br = break_path(AT_FDCWD, path);
	
	dpv(br.dirfd);
	
	dpv(br.fd);
	
	struct scope* scope = new_scope(grammar);
	
	struct pragma_once* pragma_once = new_pragma_once();
	
	recursive_parse(
		/* options: */ options,
		/* scope: */ scope,
		/* pragma_once: */ pragma_once,
		/* scratchpad: */ scratchpad,
		/* absolute_dirfd: */ br.dirfd,
		/* relative_dirfd: */ br.dirfd,
		/* fd: */ br.fd,
		/* lex: */ lex
	);
	
	TODO;
	#if 0
	free_pragma_once(pragma_once);
	
	resolve_grammar_names(scope);
	
	free_scope(scope);
	#endif
	
	if (br.dirfd > 0)
		close(br.dirfd);
	
	close(br.fd);
	
	EXIT;
}
















