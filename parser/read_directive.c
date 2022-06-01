
#include <debug.h>

#include <macros/memequals.h>

#include "tokenizer/struct.h"
#include "tokenizer/read_token.h"
#include "tokenizer/machines/include.h"

#include "recursive_parse.h"
#include "read_directive.h"

int read_directive(
	struct tokenizer* tokenizer,
	struct avl_tree_t* grammar,
	struct avl_tree_t* fragments,
	struct pragma_once* pragma_once,
	struct memory_arena* token_scratchpad,
	int absolute_dirfd,
	int relative_dirfd,
	struct lex* lex)
{
	int error = 0;
	ENTER;
	
	if (memequals(tokenizer->tokenchars.chars, "%""start", 7))
	{
		TODO;
	}
	else if (memequals(tokenizer->tokenchars.chars, "%""include", 9))
	{
		error = read_token(tokenizer, include_machine);
		
		switch (tokenizer->token)
		{
			case t_relative_path:
				TODO;
				break;
			
			case t_absolute_path:
			{
				char* path = (char*) tokenizer->tokenchars.chars + 1;
				
				path[tokenizer->tokenchars.n - 2] = '\0';
				
				dpvs(path);
				
				error = recursive_parse(
					/* grammar: */ grammar,
					/* fragments: */ fragments,
					/* pragma_once: */ pragma_once,
					/* token_scratchpad: */ token_scratchpad,
					/* absolute_dirfd: */ absolute_dirfd,
					/* relative_dirfd: */ relative_dirfd,
					/* path */ path,
					/* lex: */ lex);
				
				TODO;
				break;
			}
			
			default:
				TODO;
				break;
		}
		
		TODO;
	}
	else
	{
		dpvs(tokenizer->tokenchars.chars);
		TODO;
		error = e_bad_input_file;
	}
	
	EXIT;
	return error;
}















