
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>

#include <debug.h>

#include <cmdln/input_path.h>
#include <cmdln/make_dependencies.h>

#include <lex/add_EOF_token.h>

#include <misc/canonicalize_path.h>

#include "scope/new.h"
#include "scope/free.h"

#include "pragma_once/new.h"
#include "pragma_once/print_dependencies.h"
#include "pragma_once/free.h"

#include "main_parse.h"
#include "resolve_grammar_names.h"
#include "recursive_parse.h"

void main_parse(
	struct avl_tree_t* grammar,
	struct avl_tree_t* extra_fields,
	struct lex* lex)
{
	ENTER;
	
	dpvs(input_path);
	
	struct scope* scope = new_scope(grammar);
	
	struct pragma_once* pragma_once = new_pragma_once();
	
	char* root_path = canonicalize_path(input_path);
	
	recursive_parse(
		/* pragma_once: */ pragma_once,
		/* extra_fields: */ extra_fields,
		/* scope: */ scope,
		/* lex: */ lex,
		/* root_path: */ root_path,
		/* curr_path: */ root_path
	);
	
	free(root_path);
	
	resolve_grammar_names(scope);
	
	lex_add_EOF_token(lex);
	
	if (make_dependencies)
		pragma_once_print_dependencies(pragma_once);
	
	free_pragma_once(pragma_once);
	
	free_scope(scope);
	
	EXIT;
}















