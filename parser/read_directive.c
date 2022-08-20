
#include <assert.h>

#include <stdlib.h>

#include <macros/strequals.h>

#include <enums/error.h>

#include <debug.h>

#include <memory/sstrdup.h>
#include <memory/smemdup.h>
#include <memory/smalloc.h>

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
#include "tokenizer/machines/root.h"

#include "scope/declare/grammar.h"

#include "grammar/root.h"

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
	
	if (strequals(tokenizer->tokenchars.chars, "%""start"))
	{
		read_token(tokenizer, colon_machine);
		
		// prep production-rule reader:
		read_token(tokenizer, production_root_machine);
		
		// read a prodution rule:
		struct gbundle bundle = read_root_production(
			/* tokenizer:  */ tokenizer,
			/* scratchpad: */ scratchpad,
			/* options:    */ options,
			/* scope:      */ scope,
			/* lex:        */ lex);
		
		bundle.end->is_reduction_point = true;
		
		struct gegex* nfa_start = bundle.start;
		
		// nfa to dfa
		struct gegex* dfa_start = gegex_nfa_to_dfa(nfa_start, scratchpad);
		
		// simplify
		struct gegex* simp_start = gegex_simplify_dfa(dfa_start, scratchpad);
		
		// add grammar rule to scope
		scope_declare_grammar(scope, "(start)", simp_start);
		
		free_gegex(nfa_start, scratchpad);
		free_gegex(dfa_start, scratchpad);
	}
	else if (strequals(tokenizer->tokenchars.chars, "%""skip"))
	{
		free_regex(options->skip, scratchpad);
		
		read_token(tokenizer, colon_machine);
		
		read_token(tokenizer, regex_root_machine);
		
		struct rbundle bun = read_root_token_expression(tokenizer, scratchpad, scope, options->token_skip);
		
		if (!bun.is_nfa)
		{
			bun = regex_dfa_to_nfa(bun.dfa, scratchpad);
		}
		
		regex_add_lambda_transition(bun.nfa.end, scratchpad, bun.nfa.start);
		
		options->skip = bun.nfa.start;
	}
	else if (strequals(tokenizer->tokenchars.chars, "%""token_skip"))
	{
		free_regex(options->skip, scratchpad);
		
		read_token(tokenizer, colon_machine);
		
		read_token(tokenizer, regex_root_machine);
		
		struct rbundle bun = read_root_token_expression(tokenizer, scratchpad, scope, options->token_skip);
		
		if (!bun.is_nfa)
		{
			bun = regex_dfa_to_nfa(bun.dfa, scratchpad);
		}
		
		regex_add_lambda_transition(bun.nfa.end, scratchpad, bun.nfa.start);
		
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
				
				unsigned char* dup = smemdup(tokenizer->tokenchars.chars, tokenizer->tokenchars.n);
				
				return (struct dop) {
					.kind = dk_string,
					.s.chars = dup,
					.s.len = tokenizer->tokenchars.n};
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
		
		struct dlink* dlink = smalloc(sizeof(*dlink));
		
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
		switch (read_token(tokenizer, include_machine))
		{
			case t_relative_path:
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















