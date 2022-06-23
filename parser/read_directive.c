
#include <debug.h>

#include <macros/memequals.h>

#include <memory/sstrdup.h>

#include "options/struct.h"

#include "tokenizer/struct.h"
#include "tokenizer/read_token.h"
#include "tokenizer/machines/include.h"
#include "tokenizer/machines/identifier.h"
#include "tokenizer/machines/semicolon.h"
#include "tokenizer/machines/root.h"

#include "recursive_parse.h"
#include "read_directive.h"

void read_directive(
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct pragma_once* pragma_once,
	struct memory_arena* scratchpad,
	int absolute_dirfd,
	int relative_dirfd,
	struct lex* lex)
{
	ENTER;
	
	if (memequals(tokenizer->tokenchars.chars, "%""start", 7))
	{
		read_token(tokenizer, identifier_machine);
		
		free(options->start_rule);
		
		options->start_rule = sstrdup(tokenizer->tokenchars.chars);
		
		dpvs(options->start_rule);
		
		read_token(tokenizer, semicolon_machine);
	}
	else if (memequals(tokenizer->tokenchars.chars, "%""include", 9))
	{
		switch (read_token(tokenizer, include_machine))
		{
			case t_relative_path:
			{
				TODO;
				break;
			}
			
			case t_absolute_path:
			{
				char* path = (char*) tokenizer->tokenchars.chars + 1;
				
				path[tokenizer->tokenchars.n - 2] = '\0';
				
				dpvs(path);
				
				recursive_parse(
					/* options: */ options,
					/* scope: */ scope,
					/* pragma_once: */ pragma_once,
					/* token_scratchpad: */ scratchpad,
					/* absolute_dirfd: */ absolute_dirfd,
					/* relative_dirfd: */ relative_dirfd,
					/* path */ path,
					/* lex: */ lex);
				
				break;
			}
			
			default:
				TODO;
				break;
		}
	}
	else
	{
		dpvs(tokenizer->tokenchars.chars);
		TODO;
		exit(e_bad_input_file);
	}
	
	EXIT;
}















