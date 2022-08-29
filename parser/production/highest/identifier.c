
#include <debug.h>

#include <parser/tokenizer/struct.h>
#include <parser/tokenizer/read_token.h>
#include <parser/tokenizer/machines/production/after_highest.h>

#include <parser/scope/lookup/inline_grammar.h>
#include <parser/scope/build_absolute_name.h>

#include <yacc/gegex/state/new.h>
#include <yacc/gegex/state/add_grammar_transition.h>

#include <set/string/new.h>
#include <set/string/add.h>

#include "identifier.h"

struct gbundle read_identifier_production(
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct lex* lex)
{
	struct gbundle retval;
	ENTER;
	
	dpvs(tokenizer->tokenchars.chars);
	
	struct gegex* inlined;
	
	if ((inlined = scope_lookup_inline_grammar(scope, (void*) tokenizer->tokenchars.chars)))
	{
		TODO;
		#if 0
		#ifdef WITH_ARENAS
		retval = gegex_clone_nfa(grammar_arena, inlined.start, inlined.end);
		#else
		retval = gegex_clone_nfa(inlined.start, inlined.end);
		#endif
		#endif
		
		read_token(tokenizer, production_after_highest_machine);
	}
	else
	{
		char* full_name = scope_build_absolute_name(scope, (char*) tokenizer->tokenchars.chars, tokenizer->tokenchars.n);
		
		struct stringset* tags = new_stringset();
		
		read_token(tokenizer, production_after_highest_machine);
		
		while (tokenizer->token == t_hashtag)
		{
			char* dup = strdup((void*) tokenizer->tokenchars.chars);
			
			stringset_add(tags, dup);
			
			read_token(tokenizer, production_after_highest_machine);
		}
		
		struct gegex* start = new_gegex();
		struct gegex* end = new_gegex();
		
		gegex_add_grammar_transition(start, full_name, end);
		
		retval = (struct gbundle) {start, end};
	}
	
	#ifdef DOTOUT
	gegex_dotout(retval.start, retval.end, __PRETTY_FUNCTION__);
	#endif
	
	EXIT;
	return retval;
}

















