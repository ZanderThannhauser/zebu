
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

#include <debug.h>

#include <enums/error.h>

#include <macros/strequals.h>

/*#include <enums/error.h>*/

#include <arena/malloc.h>

#include <misc/break_path.h>

#include "options/struct.h"
#include "options/dlink.h"

#include <lex/regex/state/free.h>
#include <lex/regex/dfa_to_nfa.h>
#include <lex/regex/state/add_lambda_transition.h>

#include <yacc/gegex/state/struct.h>
#include <yacc/gegex/state/free.h>
#include <yacc/gegex/nfa_to_dfa/nfa_to_dfa.h>
#include <yacc/gegex/simplify_dfa/simplify_dfa.h>

#include "tokenizer/struct.h"
#include "tokenizer/read_token.h"
#include "tokenizer/machines/include.h"
#include "tokenizer/machines/production/root.h"
#include "tokenizer/machines/misc/semicolon.h"
#include "tokenizer/machines/misc/colon.h"
#include "tokenizer/machines/misc/identifier_or_string.h"
#include "tokenizer/machines/misc/comparision.h"
#include "tokenizer/machines/regex/root.h"
/*#include "tokenizer/machines/root.h"*/

#include "scope/declare/grammar.h"

#include "grammar/root.h"

#include "token/root.h"

#include "recursive_parse.h"

#include "read_directive.h"

void read_directive(
	#ifdef WITH_ARENAS
	struct memory_arena* parser_arena,
	struct memory_arena* grammar_arena,
	struct memory_arena* token_arena,
	#endif
	struct tokenizer* tokenizer,
	struct options* options,
	struct scope* scope,
	struct pragma_once* pragma_once,
	int absolute_dirfd,
	int relative_dirfd,
	struct lex* lex)
{
	ENTER;
	
	dpvs(tokenizer->tokenchars.chars);
	
	if (strequals(tokenizer->tokenchars.chars, "%""start"))
	{
		read_token(tokenizer, colon_machine);
		
		// prep production-rule reader:
		read_token(tokenizer, production_root_machine);
		
		// read a prodution rule:
		struct gbundle bundle = read_root_production(
			#ifdef WITH_ARENAS
			/* grammar_arena: */ grammar_arena,
			/*   token_arena: */ token_arena,
			#endif
			/*     tokenizer: */ tokenizer,
			/*       options: */ options,
			/*         scope: */ scope,
			/*           lex: */ lex);
		
		bundle.end->is_reduction_point = true;
		
		struct gegex* nfa_start = bundle.start;
		
		// nfa to dfa
		#ifdef WITH_ARENAS
		struct gegex* dfa_start = gegex_nfa_to_dfa(grammar_arena, nfa_start);
		#else
		struct gegex* dfa_start = gegex_nfa_to_dfa(nfa_start);
		#endif
		
		// simplify
		#ifdef WITH_ARENAS
		struct gegex* simp_start = gegex_simplify_dfa(grammar_arena, dfa_start);
		#else
		struct gegex* simp_start = gegex_simplify_dfa(dfa_start);
		#endif
		
		// add grammar rule to scope
		scope_declare_grammar(scope, "(start)", simp_start);
		
		free_gegex(nfa_start), free_gegex(dfa_start);
	}
	else if (strequals(tokenizer->tokenchars.chars, "%""skip"))
	{
		free_regex(options->skip), options->skip = NULL;
		
		read_token(tokenizer, colon_machine);
		
		read_token(tokenizer, regex_root_machine);
		
		#ifdef WITH_ARENAS
		struct rbundle bun = read_root_token_expression(parser_arena, tokenizer, scope, options->token_skip);
		#else
		struct rbundle bun = read_root_token_expression(tokenizer, scope, options->token_skip);
		#endif
		
		if (!bun.is_nfa)
		{
			#ifdef WITH_ARENAS
			bun = regex_dfa_to_nfa(parser_arena, bun.dfa);
			#else
			bun = regex_dfa_to_nfa(bun.dfa);
			#endif
		}
		
		regex_add_lambda_transition(bun.nfa.end, bun.nfa.start);
		
		options->skip = bun.nfa.start;
	}
	else if (strequals(tokenizer->tokenchars.chars, "%""token_skip"))
	{
		free_regex(options->token_skip), options->token_skip = NULL;
		
		read_token(tokenizer, colon_machine);
		
		read_token(tokenizer, regex_root_machine);
		
		#ifdef WITH_ARENAS
		struct rbundle bun = read_root_token_expression(parser_arena, tokenizer, scope, options->token_skip);
		#else
		struct rbundle bun = read_root_token_expression(tokenizer, scope, options->token_skip);
		#endif
		
		if (!bun.is_nfa)
		{
			#ifdef WITH_ARENAS
			bun = regex_dfa_to_nfa(parser_arena, bun.dfa);
			#else
			bun = regex_dfa_to_nfa(bun.dfa);
			#endif
		}
		
		regex_add_lambda_transition(bun.nfa.end, bun.nfa.start);
		
		options->token_skip = bun.nfa.start;
	}
	else if (strequals(tokenizer->tokenchars.chars, "%""disambiguate"))
	{
		read_token(tokenizer, colon_machine);
		
		struct dop read_dop()
		{
			read_token(tokenizer, identifier_or_string_machine);
			
			if (tokenizer->token == t_identifier)
			{
				dpvs(tokenizer->tokenchars.chars);
				
				if (strequals(tokenizer->tokenchars.chars, "literal"))
				{
					return (struct dop) {.kind = dk_literal};
				}
				else if (strequals(tokenizer->tokenchars.chars, "regex"))
				{
					return (struct dop) {.kind = dk_regex};
				}
				else
				{
					TODO;
				}
			}
			else if (tokenizer->token == t_string_literal)
			{
				dpvsn(tokenizer->tokenchars.chars, tokenizer->tokenchars.n);
				
				TODO;
				#if 0
				unsigned char* dup = smemdup(tokenizer->tokenchars.chars, tokenizer->tokenchars.n);
				
				return (struct dop) {
					.kind = dk_string,
					.s.chars = dup,
					.s.len = tokenizer->tokenchars.n};
				#endif
			}
			else
			{
				TODO;
				exit(1);
			}
		}
		
		struct dop left = read_dop();
		
		read_token(tokenizer, comparision_machine);
		
		int cmp;
		
		switch (tokenizer->token)
		{
			case t_lthan: cmp = -1; break;
			case t_gthan: cmp = +1; break;
			case t_equal_to: cmp = 0; break;
			default: TODO break;
		}
		
		struct dop right = read_dop();
		
		#ifdef WITH_ARENAS
		struct dlink* dlink = arena_malloc(options->arena, sizeof(*dlink));
		#else
		struct dlink* dlink = malloc(sizeof(*dlink));
		#endif
		
		dlink->left = left;
		dlink->cmp = cmp;
		dlink->right = right;
		dlink->next = NULL;
		
		if (options->disambiguatations.head)
		{
			options->disambiguatations.tail->next = dlink;
			options->disambiguatations.tail = dlink;
		}
		else
		{
			options->disambiguatations.head = dlink;
			options->disambiguatations.tail = dlink;
		}
		
		read_token(tokenizer, semicolon_machine);
	}
	else if (strequals(tokenizer->tokenchars.chars, "%""include"))
	{
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
		
		struct br_rettype br = break_path(dirfd, tokenizer->tokenchars.chars);
		
		recursive_parse(
			#ifdef WITH_ARENAS
			/* parser_arena: */ parser_arena,
			/* grammar_arena: */ grammar_arena,
			/* token_arena: */ token_arena,
			#endif
			/* options: */ options,
			/* scope: */ scope,
			/* pragma_once: */ pragma_once,
			/* absolute_dirfd: */ absolute_dirfd,
			/* relative_dirfd: */ br.dirfd,
			/* fd */ br.fd,
			/* lex: */ lex);
		
		if (br.dirfd > 0 && br.dirfd != dirfd)
			close(br.dirfd);
		
		close(br.fd);
	}
	else
	{
		dpvs(tokenizer->tokenchars.chars);
		TODO;
		exit(e_bad_input_file);
	}
	
	EXIT;
}















