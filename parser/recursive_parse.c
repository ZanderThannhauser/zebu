
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <strings.h>

#include <debug.h>

/*#include <misc/sopenat.h>*/
#include <enums/error.h>

#include "tokenizer/struct.h"
#include "tokenizer/new.h"
#include "tokenizer/read_char.h"
#include "tokenizer/read_token.h"
#include "tokenizer/token_names.h"
#include "tokenizer/free.h"

#include "pragma_once/lookup.h"

#include "read_charset.h"
#include "read_fragment.h"
#include "read_grammar.h"
#include "read_inline_grammar.h"
#include "read_directive.h"

#include "recursive_parse.h"

void recursive_parse(
	struct pragma_once* pragma_once,
	struct avl_tree_t* extra_fields,
	struct scope* scope,
	struct lex* lex,
	const char* root_path,
	const char* curr_path)
{
	ENTER;
	
	dpvs(root_path);
	dpvs(curr_path);
	
	bool first_time = pragma_once_lookup(pragma_once, curr_path);
	
	dpvb(first_time);
	
	if (first_time)
	{
		int fd = open(curr_path, O_RDONLY);
		
		if (fd < 0)
		{
			TODO;
			exit(e_syscall_failed);
		}
		
		
		struct tokenizer *tokenizer = new_tokenizer(fd);
		
		read_char(tokenizer);
		
		read_token(tokenizer);
		
		while (tokenizer->token != t_EOF)
		{
			switch (tokenizer->token)
			{
				case t_percent:
				{
					read_directive(
						/* pragma_once:  */ pragma_once,
						/* extra_fields: */ extra_fields,
						/* tokenizer:    */ tokenizer,
						/* scope:        */ scope,
						/* lex:          */ lex,
						/* root_path:    */ root_path,
						/* curr_path:    */ curr_path);
					break;
				}
				
				case t_osquare:
				{
					read_charset(tokenizer, scope);
					
					if (tokenizer->token != t_semicolon)
					{
						fprintf(stderr, "zebu: encountered syntax error on line %u: "
							"unexpected '%s', expecting '%s'!\n",
							tokenizer->line,
							token_names[tokenizer->token],
							token_names[t_semicolon]);
						exit(e_syntax_error);
					}
					
					read_token(tokenizer);
					break;
				}
				
				case t_gravemark:
				{
					read_fragment(tokenizer, scope);
					
					if (tokenizer->token != t_semicolon)
					{
						fprintf(stderr, "zebu: encountered syntax error on line %u: "
							"unexpected '%s', expecting '%s'!\n",
							tokenizer->line,
							token_names[tokenizer->token],
							token_names[t_semicolon]);
						exit(e_syntax_error);
					}
					
					read_token(tokenizer);
					break;
				}
				
				case t_oparen:
				{
					read_inline_grammar(tokenizer, scope, lex);
					
					if (tokenizer->token != t_semicolon)
					{
						fprintf(stderr, "zebu: encountered syntax error on line %u: "
							"unexpected '%s', expecting '%s'!\n",
							tokenizer->line,
							token_names[tokenizer->token],
							token_names[t_semicolon]);
						exit(e_syntax_error);
					}
					
					read_token(tokenizer);
					break;
				}
				
				case t_identifier:
				{
					read_grammar(tokenizer, scope, lex);
					
					if (tokenizer->token != t_semicolon)
					{
						fprintf(stderr, "zebu: encountered syntax error on line %u: "
							"unexpected '%s', expecting '%s'!\n",
							tokenizer->line,
							token_names[tokenizer->token],
							token_names[t_semicolon]);
						exit(e_syntax_error);
					}
					
					read_token(tokenizer);
					break;
				}
				
				default:
					dpv(tokenizer->token);
					TODO;
					break;
			}
		}
		
		free_tokenizer(tokenizer);
	}
	
	EXIT;
}














