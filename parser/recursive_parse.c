
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <strings.h>

#include <debug.h>

/*#include <misc/sopenat.h>*/

#include "options/struct.h"

#include "tokenizer/struct.h"
#include "tokenizer/new.h"
#include "tokenizer/read_char.h"
#include "tokenizer/read_token.h"
#include "tokenizer/machines/root.h"
#include "tokenizer/free.h"

#include "pragma_once/lookup.h"

#include "read_directive/read_directive.h"
#include "read_charset.h"
#include "read_fragment.h"
#include "read_grammar.h"
#include "read_inline_grammar.h"

#include "recursive_parse.h"

void recursive_parse(
	struct pragma_once* pragma_once,
	struct options* options,
	struct scope* scope,
	struct lex* lex,
	int absolute_dirfd,
	int relative_dirfd,
	int fd)
{
	ENTER;
	
	bool first_time = pragma_once_lookup(pragma_once, fd);
	
	dpvb(first_time);
	
	if (first_time)
	{
		struct tokenizer *tokenizer = new_tokenizer(fd);
		
		read_char(tokenizer);
		
		read_token(tokenizer, root_machine);
		
		while (tokenizer->token != t_EOF)
		{
			switch (tokenizer->token)
			{
				case t_directive:
				{
					read_directive(
						/* pragma_once:    */ pragma_once,
						/* tokenizer:      */ tokenizer,
						/* options:        */ options,
						/* scope:          */ scope,
						/* lex:            */ lex,
						/* absolute_dirfd: */ absolute_dirfd,
						/* relative_dirfd: */ relative_dirfd);
					break;
				}
				
				case t_bracketed_identifier:
				{
					read_charset(
						/* tokenizer: */ tokenizer,
						/* scope      */ scope);
					break;
				}
				
				case t_gravemarked_identifier:
				{
					read_fragment(
						/* tokenizer:  */ tokenizer,
						/* scope       */ scope
					);
					break;
				}
				
				case t_parenthesised_identifier:
				{
					read_inline_grammar(
						/* tokenizer: */ tokenizer,
						/* options: */ options,
						/* scope: */ scope,
						/* lex: */ lex);
					break;
				}
				
				case t_identifier:
				{
					read_grammar(
						/* tokenizer:   */ tokenizer,
						/* options:     */ options,
						/* scope        */ scope,
						/* lex:         */ lex);
					break;
				}
				
				default:
					dpv(tokenizer->token);
					TODO;
					break;
			}
			
			read_token(tokenizer, root_machine);
		}
		
		free_tokenizer(tokenizer);
	}
	
	EXIT;
}














