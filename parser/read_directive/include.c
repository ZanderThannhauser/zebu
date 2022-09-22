
#include <assert.h>
#include <unistd.h>

#include <debug.h>

#include <misc/break_and_open_path.h>

#include <parser/tokenizer/struct.h>
#include <parser/tokenizer/read_token.h>

#include "../recursive_parse.h"

#include "include.h"

void read_include_directive(
	struct pragma_once* pragma_once,
	struct avl_tree_t* extra_fields,
	struct tokenizer* tokenizer,
	struct scope* scope,
	struct lex* lex,
	int absolute_dirfd,
	int relative_dirfd)
{
	ENTER;
	
	assert(tokenizer->token == t_identifier);
	
	read_token(tokenizer);
	
	unsigned dirfd;
	
	switch (tokenizer->token)
	{
		case t_string_literal:
			dirfd = relative_dirfd;
			break;
		
		case t_absolute_path:
			dirfd = absolute_dirfd;
			break;
		
		default:
			TODO;
			break;
	}
	
	dpvs(tokenizer->tokenchars.chars);
	
	struct br_rettype br = break_and_open_path(dirfd, tokenizer->tokenchars.chars);
	
	recursive_parse(
		/* pragma_once: */ pragma_once,
		/* extra_fields: */ extra_fields,
		/* scope: */ scope,
		/* lex: */ lex,
		/* absolute_dirfd: */ absolute_dirfd,
		/* relative_dirfd: */ br.dirfd,
		/* fd */ br.fd);
	
	if (br.dirfd > 0 && br.dirfd != dirfd)
		close(br.dirfd);
	
	close(br.fd);
	
	EXIT;
}











