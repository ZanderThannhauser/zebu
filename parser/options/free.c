
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <lex/regex/state/free.h>

#include <arena/dealloc.h>

#include "dlink.h"
#include "struct.h"
#include "free.h"

static void free_dlink(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct dlink* dlink
) {
	ENTER;
	
	if (dlink)
	{
		switch (dlink->left.kind)
		{
			case dk_literal: break;
			case dk_regex: break;
			case dk_string:
			{
				#ifdef WITH_ARENAS
				arena_dealloc(arena, dlink->left.s.chars);
				#else
				free(dlink->left.s.chars);
				#endif
				break;
			}
		}
		
		switch (dlink->right.kind)
		{
			case dk_literal: break;
			case dk_regex: break;
			case dk_string:
			{
				#ifdef WITH_ARENAS
				arena_dealloc(arena, dlink->right.s.chars);
				#else
				free(dlink->right.s.chars);
				#endif
				break;
			}
		}
		
		#ifdef WITH_ARENAS
		free_dlink(arena, dlink->next);
		#else
		free_dlink(dlink->next);
		#endif
		
		#ifdef WITH_ARENAS
		arena_dealloc(arena, dlink);
		#else
		free(dlink);
		#endif
	}
	
	EXIT;
}

void free_options(struct options* this)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	free_dlink(this->arena, this->disambiguatations.head);
	#else
	free_dlink(this->disambiguatations.head);
	#endif
	
	// free_regex(this->skip);
	// free_regex(this->token_skip);
	
	#ifdef WITH_ARENAS
	arena_dealloc(this->arena, this);
	#else
	free(this);
	#endif
	
	EXIT;
}











