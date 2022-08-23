
#include <unistd.h>
#include <stdlib.h>

#include <assert.h>

#include <fcntl.h>

#include <debug.h>

/*#include <avl/avl.h>*/
/*#include <avl/new.h>*/

#include <misc/sopen.h>
#include <misc/sopenat.h>
#include <misc/break_path.h>

#include <arena/mmap/new.h>
#include <arena/free.h>

/*#include <set/of_strs/add.h>*/

#include "options/struct.h"

#include <lex/add_EOF_token.h>

#include "scope/new.h"
#include "scope/free.h"

#include "pragma_once/new.h"
#include "pragma_once/free.h"

#include "resolve_grammar_names.h"
#include "recursive_parse.h"
#include "mains_parse.h"

void mains_parse(
	struct memory_arena* grammar_arena,
	struct memory_arena* token_arena,
	struct options* options,
	struct avl_tree_t* grammar,
	struct lex* lex,
	const char* path)
{
	ENTER;
	
	struct memory_arena* parser_arena = new_mmap_arena();
	
	struct scope* scope = new_scope(parser_arena, grammar_arena, grammar);
	
	struct pragma_once* pragma_once = new_pragma_once(parser_arena);
	
	struct br_rettype br = break_path(AT_FDCWD, path);
	
	recursive_parse(
		/* parser_arena: */ parser_arena,
		/* grammar_arena: */ grammar_arena,
		/* token_arena: */ token_arena,
		/* options: */ options,
		/* scope: */ scope,
		/* pragma_once: */ pragma_once,
		/* absolute_dirfd: */ br.dirfd,
		/* relative_dirfd: */ br.dirfd,
		/* fd: */ br.fd,
		/* lex: */ lex
	);
	
	resolve_grammar_names(scope);
	
	lex_add_EOF_token(lex, options->skip);
	
	free_memory_arena(parser_arena);
	
	if (br.dirfd > 0)
		close(br.dirfd);
	
	close(br.fd);
	
	EXIT;
}
















