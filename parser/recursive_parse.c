
#include <debug.h>

#include <misc/sopenat.h>

#include "tokenizer/struct.h"
#include "tokenizer/new.h"
#include "tokenizer/read_char.h"
#include "tokenizer/read_token.h"
#include "tokenizer/machines/root.h"
#include "tokenizer/free.h"

#include "pragma_once/lookup.h"

#include "read_directive.h"
#include "read_fragment.h"

#include "recursive_parse.h"

int recursive_parse(
	struct avl_tree_t* grammar,
	struct avl_tree_t* fragments,
	struct pragma_once* pragma_once,
	struct memory_arena* token_scratchpad,
	int absolute_dirfd,
	int relative_dirfd,
	char* path,
	struct lex* lex)
{
	int error = 0;
	ENTER;
	
	int new_relative_dirfd = -1;
	
	int fd = -1;
	
	{
		char* slash = rindex(path, '/');
		
		if (slash)
		{
			*slash = '\0';
			
			error = sopenat(&new_relative_dirfd, relative_dirfd, path, O_PATH);
			
			path = slash + 1;
		}
		else
		{
			new_relative_dirfd = relative_dirfd;
		}
	}
	
	bool first_time;
	
	if (!error) error = 0
		?: sopenat(&fd, new_relative_dirfd, path, O_RDONLY)
		?: pragma_once_lookup(pragma_once, &first_time, fd);
	
	#ifdef DEBUGGING
	if (!error)
	{
		dpvb(first_time);
	}
	#endif
	
	if (!error && first_time)
	{
		struct tokenizer *tokenizer = NULL;
		
		error = 0
			?: new_tokenizer(&tokenizer, fd)
			?: read_char(tokenizer)
			?: read_token(tokenizer, root_machine);
		
		while (!error && tokenizer->token != t_EOF)
		{
			switch (tokenizer->token)
			{
				case t_directive:
				{
					error = read_directive(
						/* tokenizer: */ tokenizer,
						/* grammar: */ grammar,
						/* fragments: */ fragments,
						/* pragma_once: */ pragma_once,
						/* token_scratchpad: */ token_scratchpad,
						/* absolute_dirfd: */ absolute_dirfd,
						/* relative_dirfd: */ new_relative_dirfd,
						/* lex: */ lex);
					TODO;
					break;
				}
				
				case t_fragment:
				{
					error = read_fragment(
						/* tokenizer: */ tokenizer,
						/* token_scratchpad: */ token_scratchpad,
						/* lex: */ lex);
					TODO;
					break;
				}
				
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
		
		free_tokenizer(tokenizer);
	}
	
	TODO;
	
	if (new_relative_dirfd > 0 && new_relative_dirfd != relative_dirfd)
		close(new_relative_dirfd);
	
	if (fd > 0)
		close(fd);
	
	EXIT;
	return error;
}















