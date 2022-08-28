
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>

#include <debug.h>

#include <cmdln/input_path.h>

/*#include <avl/avl.h>*/
/*#include <avl/new.h>*/

/*#include <misc/sopen.h>*/
/*#include <misc/sopenat.h>*/

/*#include <arena/mmap/new.h>*/
/*#include <arena/free.h>*/

/*#include <set/of_strs/add.h>*/

/*#include "options/struct.h"*/

/*#include <lex/add_EOF_token.h>*/

/*#include "resolve_grammar_names.h"*/

#include <misc/break_and_open_path.h>

#include "options/new.h"
#include "options/free.h"

#include "scope/new.h"
#include "scope/free.h"

#include "pragma_once/new.h"
#include "pragma_once/free.h"

#include "main_parse.h"
#include "recursive_parse.h"

void main_parse(struct avl_tree_t* grammar, struct lex* lex)
{
	ENTER;
	
	dpvs(input_path);
	
	struct options* options = new_options();
	
	struct scope* scope = new_scope(grammar);
	
	struct pragma_once* pragma_once = new_pragma_once();
	
	struct br_rettype br = break_and_open_path(AT_FDCWD, (void*) input_path);
	
	recursive_parse(
		/* pragma_once: */ pragma_once,
		/* options: */ options,
		/* scope: */ scope,
		/* lex: */ lex,
		/* absolute_dirfd: */ br.dirfd,
		/* relative_dirfd: */ br.dirfd,
		/* fd: */ br.fd
	);
	
	TODO;
	#if 0
	resolve_grammar_names(scope);
	
	lex_add_EOF_token(lex, options->skip);
	
	if (options->disambiguatations.head)
	{
		lex_process_disambiguatations(lex, options->disambiguatations.head);
	}
	#endif
	
	if (br.dirfd > 0)
		close(br.dirfd);
	
	close(br.fd);
	
	free_pragma_once(pragma_once);
	free_options(options);
	free_scope(scope);
	
	EXIT;
}















