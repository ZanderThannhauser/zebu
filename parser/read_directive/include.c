
#include <assert.h>
#include <unistd.h>

#include <debug.h>

#include <misc/break_and_open_path.h>

#include <parser/tokenizer/struct.h>
#include <parser/tokenizer/read_token.h>
#include <parser/tokenizer/machines/misc/include.h>

#include "../recursive_parse.h"

#include "include.h"

void read_include_directive(
	struct pragma_once* pragma_once,
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex,
	int absolute_dirfd,
	int relative_dirfd)
{
	ENTER;
	
	enum token token = read_token(tokenizer, include_machine);
	
	unsigned dirfd;
	
	switch (token)
	{
		case t_relative_path:
			dirfd = relative_dirfd;
			break;
		
		case t_absolute_path:
			dirfd = absolute_dirfd;
			break;
		
		default:
			TODO;
			break;
	}
	
	struct br_rettype br = break_and_open_path(dirfd, tokenizer->tokenchars.chars);
	
	recursive_parse(
		/* pragma_once: */ pragma_once,
		/* options: */ options,
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











