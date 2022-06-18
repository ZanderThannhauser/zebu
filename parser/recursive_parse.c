
#include <debug.h>

#include <misc/sopenat.h>

#include "tokenizer/struct.h"
#include "tokenizer/new.h"
#include "tokenizer/read_char.h"
#include "tokenizer/read_token.h"
#include "tokenizer/machines/root.h"
/*#include "tokenizer/free.h"*/

#include "pragma_once/lookup.h"

#include "read_directive.h"
#include "read_fragment.h"

#include "recursive_parse.h"

void recursive_parse(
	struct avl_tree_t* grammar,
	struct avl_tree_t* fragments,
	struct pragma_once* pragma_once,
	struct memory_arena* scratchpad,
	int absolute_dirfd,
	int old_relative_dirfd,
	char* path,
	struct lex* lex)
{
	int error = 0;
	ENTER;
	
	int relative_dirfd = -1;
	
	{
		char* slash = rindex(path, '/');
		
		if (slash)
		{
			*slash = '\0';
			
			relative_dirfd = sopenat(old_relative_dirfd, path, O_PATH);
			
			path = slash + 1;
		}
		else
		{
			relative_dirfd = old_relative_dirfd;
		}
	}
	
	int fd = sopenat(relative_dirfd, path, O_RDONLY);
	
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
				case t_directive: read_directive(
					/* tokenizer:      */ tokenizer,
					/* grammar:        */ grammar,
					/* fragments:      */ fragments,
					/* pragma_once:    */ pragma_once,
					/* scratchpad:     */ scratchpad,
					/* absolute_dirfd: */ absolute_dirfd,
					/* relative_dirfd: */ relative_dirfd,
					/* lex:            */ lex);
				break;
				
				case t_fragment: read_fragment(
					/* tokenizer: */ tokenizer,
					/* token_scratchpad: */ scratchpad,
					/* lex: */ lex);
				break;
				
				case t_identifier:
				{
					TODO;
					break;
				}
				
				default:
					TODO;
					break;
			}
		}
		
		TODO;
		#if 0
		TODO;
		
		free_tokenizer(tokenizer);
		#endif
	}
	
	TODO;
	
	#if 0
	if (new_relative_dirfd > 0 && new_relative_dirfd != relative_dirfd)
		close(new_relative_dirfd);
	
	if (fd > 0)
		close(fd);
	#endif
	
	EXIT;
}















