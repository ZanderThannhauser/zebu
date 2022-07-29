
#include <assert.h>

#include <stdlib.h>

#include <enums/error.h>

#include <debug.h>

#include <macros/memequals.h>

#include <memory/sstrdup.h>

#include "options/struct.h"

#include <lex/regex/state/free.h>
#include <lex/regex/dfa_to_nfa.h>
#include <lex/regex/state/add_lambda_transition.h>

#include "tokenizer/struct.h"
#include "tokenizer/read_token.h"
#include "tokenizer/machines/include.h"
#include "tokenizer/machines/identifier.h"
#include "tokenizer/machines/semicolon.h"
#include "tokenizer/machines/colon.h"
#include "tokenizer/machines/expression/root.h"
#include "tokenizer/machines/root.h"

#include "token/root.h"

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
	
	dpvs(tokenizer->tokenchars.chars);
	
	if (memequals(tokenizer->tokenchars.chars, "%""start", 7))
	{
		read_token(tokenizer, identifier_machine);
		
		if (options->start)
		{
			TODO;
			exit(1);
		}
		
		options->start = sstrdup(tokenizer->tokenchars.chars);
		
		dpvs(options->start);
		
		read_token(tokenizer, semicolon_machine);
	}
	else if (memequals(tokenizer->tokenchars.chars, "%""skip", 6))
	{
		free_regex(options->skip, scratchpad);
		
		read_token(tokenizer, colon_machine);
		
		read_token(tokenizer, expression_root_machine);
		
		struct rbundle bun = read_root_token_expression(tokenizer, scratchpad, scope);
		
		if (!bun.is_nfa)
		{
			bun = regex_dfa_to_nfa(bun.dfa, scratchpad);
		}
		
		regex_add_lambda_transition(bun.nfa.end, scratchpad, bun.nfa.start);
		
		options->skip = bun.nfa.start;
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















