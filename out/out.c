
#include <assert.h>
#include <limits.h>
#include <string.h>

#include <debug.h>

#include <avl/alloc_tree.h>
#include <avl/insert.h>
#include <avl/free_tree.h>

#include <string/new.h>
#include <string/free.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/len.h>
#include <quack/pop.h>
#include <quack/free.h>

#include <cmdln/output_path.h>
#include <cmdln/output_prefix.h>
#include <cmdln/parser_template.h>

#include <set/yaccstate/new.h>
#include <set/yaccstate/add.h>
#include <set/yaccstate/free.h>

#include <set/lexstate/new.h>
#include <set/lexstate/add.h>
#include <set/lexstate/free.h>

#include <yacc/state/struct.h>

#include <lex/state/struct.h>

#include <yacc/structinfo/inc.h>
#include <yacc/structinfo/compare.h>
#include <yacc/structinfo/free.h>

#include "escaped/really_just_tables_source.h"
#include "escaped/really_just_tables_header.h"

#include "escaped/just_tables_source.h"
#include "escaped/just_tables_header.h"

/*#include "escaped/buffer_driven_source.h"*/
/*#include "escaped/buffer_driven_header.h"*/

#include "escaped/readline_source.h"
#include "escaped/readline_header.h"

#include "escaped/readline_with_driver_source.h"
#include "escaped/readline_with_driver_header.h"

#include "escaped/fileio_with_driver_source.h"
#include "escaped/fileio_with_driver_header.h"

/*#include "escaped/fileio_passfail_source.h"*/
/*#include "escaped/fileio_passfail_header.h"*/

/*#include "escaped/fileio_graphviz_source.h"*/
/*#include "escaped/fileio_graphviz_header.h"*/

#include "reducerule_to_id/new.h"
#include "reducerule_to_id/reducerule_to_id.h"
#include "reducerule_to_id/print_source.h"
#include "reducerule_to_id/free.h"

#include "string_to_id/new.h"
#include "string_to_id/string_to_id.h"
#include "string_to_id/free.h"

#include "ystate_to_id/new.h"
#include "ystate_to_id/ystate_to_id.h"
#include "ystate_to_id/free.h"

#include "lstate_to_id/new.h"
#include "lstate_to_id/lstate_to_id.h"
#include "lstate_to_id/free.h"

#include "unsignedset_to_id/new.h"
#include "unsignedset_to_id/unsignedset_to_id.h"
#include "unsignedset_to_id/print_source.h"
#include "unsignedset_to_id/free.h"

#include "dyntable/new.h"
#include "dyntable/set.h"
#include "dyntable/print_source.h"
#include "dyntable/free.h"

#include "dynvector/new.h"
#include "dynvector/set.h"
#include "dynvector/print_source.h"
#include "dynvector/free.h"

#include "print_structs.h"
#include "print_tree_functions.h"
#include "print_inc_functions.h"
#include "print_free_functions.h"

#include "out.h"

static struct {
	const char **source, **header;
} lookup[number_of_parser_templates] = {
	[pt_really_just_tables] = {&really_just_tables_source, &really_just_tables_header},
	[pt_just_tables] = {&just_tables_source, &just_tables_header},
	
/*	[pt_buffer_driven] = {&buffer_driven_source, &buffer_driven_header},*/
	
	[pt_readline] = {&readline_source, &readline_header},
	[pt_readline_with_driver] = {&readline_with_driver_source, &readline_with_driver_header},
	
	[pt_fileio_with_driver] = {&fileio_with_driver_source, &fileio_with_driver_header},
/*	[pt_fileio_passfail] = {&fileio_passfail_source, &fileio_passfail_header},*/
/*	[pt_fileio_graphviz] = {&fileio_graphviz_source, &fileio_graphviz_header},*/
};

void out(struct yacc_state* start)
{
	ENTER;
	
	struct ystate_to_id* ytoi = new_ystate_to_id();
	
	struct lstate_to_id* ltoi = new_lstate_to_id();
	
	struct unsignedset_to_id* ustoi = new_unsignedset_to_id();
	
	struct string_to_id* stoi = new_string_to_id();
	
	struct reducerule_to_id* rrtoi = new_reducerule_to_id();
	
	struct dynvector* EOFs = new_dynvector("lexer_EOFs");
	struct dynvector* starts = new_dynvector("lexer_starts");
	struct dynvector* accepts = new_dynvector("lexer_accepts");
	
	struct dyntable* gotos = new_dyntable("gotos");
	struct dyntable* lexer = new_dyntable("lexer");
	struct dyntable* shifts = new_dyntable("shifts");
	struct dyntable* reduces = new_dyntable("reduces");
	
	struct avl_tree_t* structinfos = avl_alloc_tree(compare_structinfos, free_structinfo);
	
	struct quack* yacc_todo = new_quack();
	struct quack* lex_todo = new_quack();
	
	struct yaccstateset* yacc_queued = new_yaccstateset();
	struct lexstateset* lex_queued = new_lexstateset();
	
	yaccstateset_add(yacc_queued, start);
	
	quack_append(yacc_todo, start);
	
	while (quack_len(yacc_todo))
	{
		struct yacc_state* const state = quack_pop(yacc_todo);
		
		unsigned yid = ystate_to_id(ytoi, state);
		
		dpv(yid);
		
		// tokenizer:
		{
			struct lex_state* lstate = state->tokenizer_start;
			
			unsigned lid = lstate_to_id(ltoi, lstate);
			
			dpv(lid);
			
			if (lexstateset_add(lex_queued, lstate))
				quack_append(lex_todo, lstate);
			
			dynvector_set(starts, yid, lid);
		}
		
		// shift transitions:
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			struct yacc_state_transition* const ele = state->transitions.data[i];
			
			unsigned tid = unsignedset_to_id(ustoi, ele->on);
			
			unsigned syid = ystate_to_id(ytoi, ele->to);
			
			dyntable_set(shifts, yid, tid, syid);
			
			if (yaccstateset_add(yacc_queued, ele->to))
				quack_append(yacc_todo, ele->to);
		}
		
		// grammar transitions:
		for (unsigned i = 0, n = state->grammar_transitions.n; i < n; i++)
		{
			struct yacc_state_grammar_transition* const ele = state->grammar_transitions.data[i];
			
			dpvs(ele->grammar);
			
			unsigned gid = string_to_id(stoi, ele->grammar);
			
			unsigned syid = ystate_to_id(ytoi, ele->to);
			
			dyntable_set(gotos, yid, gid, syid);
			
			if (yaccstateset_add(yacc_queued, ele->to))
				quack_append(yacc_todo, ele->to);
		}
		
		// reduce transitions:
		for (unsigned i = 0, n = state->reduce_transitions.n; i < n; i++)
		{
			struct yacc_state_reduce_transition* const ele = state->reduce_transitions.data[i];
			
			unsigned tid = unsignedset_to_id(ustoi, ele->on);
			
			unsigned rrid = reducerule_to_id(rrtoi, ele->reduce_as, ele->reductioninfo, ele->structinfo);
			
			if (avl_insert(structinfos, ele->structinfo))
				inc_structinfo(ele->structinfo);
			
			dyntable_set(reduces, yid, tid, rrid);
		}
	}
	
	while (quack_len(lex_todo))
	{
		struct lex_state* const state = quack_pop(lex_todo);
		
		unsigned lid = lstate_to_id(ltoi, state);
		
		dpv(lid);
		
		if (state->accepts)
		{
			if (state->kind == tk_whitespace)
			{
				dynvector_set(accepts, lid, 1);
			}
			else
			{
				unsigned tid = unsignedset_to_id(ustoi, state->accepts);
				
				dpv(tid);
				
				dynvector_set(accepts, lid, tid);
			}
		}
		
		for (unsigned i = 0, n = 256; i < n; i++)
		{
			struct lex_state* to = state->transitions[i];
			
			if (to)
			{
				unsigned slid = lstate_to_id(ltoi, to);
				
				dyntable_set(lexer, lid, i, slid);
				
				if (lexstateset_add(lex_queued, to))
					quack_append(lex_todo, to);
			}
		}
		
		if (state->EOF_transition_to)
		{
			struct lex_state* to = state->EOF_transition_to;
			
			unsigned slid = lstate_to_id(ltoi, to);
			
			dynvector_set(EOFs, lid, slid);
			
			if (lexstateset_add(lex_queued, to))
				quack_append(lex_todo, to);
		}
	}
	
	dpvs(output_path);
	dpvs(output_prefix);
	
	// header:
	{
		char path[PATH_MAX];
		
		strcat(strcpy(path, output_path), ".h");
		
		FILE* stream = fopen(path, "w");
		
		const char* template = *lookup[parser_template].header;
		
		const char* last = template, *moving, *end = template + strlen(template);
		
		while ((moving = strstr(last, "{{")))
		{
			fwrite(last, 1, moving - last, stream), moving += 2;
			
			const char* old = moving;
			
			moving = strstr(moving, "}}");
			
			unsigned len = moving - old;
			
			if (!strncmp(old, "PREFIX", len))
			{
				fputs(output_prefix, stream);
			}
			else if (!strncmp(old, "SHIFT_TABLE", len))
			{
				TODO;
/*				dyntable_print_source(shifts, output_prefix, stream);*/
			}
			else if (!strncmp(old, "REDUCE_TABLE", len))
			{
				TODO;
/*				dyntable_print_source(reduces, output_prefix, stream);*/
			}
			else if (!strncmp(old, "GOTO_TABLE", len))
			{
				TODO;
/*				dyntable_print_source(gotos, output_prefix, stream);*/
			}
			else if (!strncmp(old, "LEXER_TABLE", len))
			{
				TODO;
/*				dyntable_print_source(lexer, output_prefix, stream);*/
			}
			else if (!strncmp(old, "LEXER_ACCEPTS_TABLE", len))
			{
				TODO;
/*				dynvector_print_source(accepts, output_prefix, stream);*/
			}
			else if (!strncmp(old, "LEXER_EOF_TABLE", len))
			{
				TODO;
/*				dynvector_print_source(EOFs, output_prefix, stream);*/
			}
			else if (!strncmp(old, "PARSE_TREE_STRUCTS", len))
			{
				print_structs(structinfos, stream);
			}
			else if (!strncmp(old, "PARSE_TREE_INC_FUNCTIONS", len))
			{
				print_inc_function_prototypes(structinfos, stream);
			}
			else if (!strncmp(old, "PARSE_TREE_FREE_FUNCTIONS", len))
			{
				print_free_function_prototypes(structinfos, stream);
			}
			else
			{
				dpvsn(old, len);
				TODO;
			}
			
			last = moving + 2;
		}
		
		fwrite(last, 1, end - last, stream);
		
		fclose(stream);
	}
	
	// source:
	{
		char path[PATH_MAX];
		
		strcat(strcpy(path, output_path), ".c");
		
		FILE* stream = fopen(path, "w");
		
		char* slash = rindex(output_path, '/');
		fprintf(stream, "#include \"%s.h\"\n", slash ? slash + 1 : output_path);
		
		const char* template = *lookup[parser_template].source;
		
		const char* last = template, *moving, *end = template + strlen(template);
		
		while ((moving = strstr(last, "{{")))
		{
			fwrite(last, 1, moving - last, stream), moving += 2;
			
			const char* old = moving;
			
			moving = strstr(moving, "}}");
			
			unsigned len = moving - old;
			
			if (!strncmp(old, "PREFIX", len))
			{
				fputs(output_prefix, stream);
			}
			else if (!strncmp(old, "SHIFT_TABLE", len))
			{
				dyntable_print_source(shifts, output_prefix, stream);
			}
			else if (!strncmp(old, "REDUCE_TABLE", len))
			{
				dyntable_print_source(reduces, output_prefix, stream);
			}
			else if (!strncmp(old, "GOTO_TABLE", len))
			{
				dyntable_print_source(gotos, output_prefix, stream);
			}
			else if (!strncmp(old, "LEXER_TABLE", len))
			{
				dyntable_print_source(lexer, output_prefix, stream);
			}
			else if (!strncmp(old, "LEXER_STARTS_TABLE", len))
			{
				dynvector_print_source(starts, output_prefix, stream);
			}
			else if (!strncmp(old, "LEXER_ACCEPTS_TABLE", len))
			{
				dynvector_print_source(accepts, output_prefix, stream);
			}
			else if (!strncmp(old, "LEXER_EOF_TABLE", len))
			{
				dynvector_print_source(EOFs, output_prefix, stream);
			}
			else if (!strncmp(old, "REDUCTIONRULE_SWITCH", len))
			{
				reducerule_to_id_print_source(rrtoi, stoi, stream);
			}
			else if (!strncmp(old, "PARSE_TREE_STRUCTS", len))
			{
				print_structs(structinfos, stream);
			}
			else if (!strncmp(old, "START_GRAMMAR_ID", len))
			{
				struct string* start = new_string("$start");
				
				fprintf(stream, "%u", string_to_id(stoi, start));
				
				free_string(start);
			}
			else if (!strncmp(old, "TOKEN_IDS_TO_SETS", len))
			{
				unsignedset_to_id_print_source(ustoi, output_prefix, stream);
			}
			else if (!strncmp(old, "PARSE_TREE_PRINT_TREE_FUNCTIONS", len))
			{
				print_tree_functions(structinfos, stream);
			}
			else if (!strncmp(old, "PARSE_TREE_INC_FUNCTIONS", len))
			{
				print_inc_functions(structinfos, stream);
			}
			else if (!strncmp(old, "PARSE_TREE_FREE_FUNCTIONS", len))
			{
				print_free_functions(structinfos, stream);
			}
			else
			{
				dpvsn(old, len);
				TODO;
			}
			
			// {{PARSE_TREE_TYPES}}
			
			// {{PARSE_TREE_CONSTRUCTORS}}
			
			// {{PARSE_TREE_GRAPHVIZ_PRINTOUT}}
			
			// {{PARSE_TREE_TERMINAL_PRINTOUT}}
			
			// {{PARSE_TREE_DESTRUCTORS}}
			
			last = moving + 2;
		}
		
		fwrite(last, 1, end - last, stream);
		
		fclose(stream);
	}
	
	avl_free_tree(structinfos);
	
	free_reducerule_to_id(rrtoi);
	
	free_unsignedset_to_id(ustoi);
	
	free_yaccstateset(yacc_queued);
	
	free_lexstateset(lex_queued);
	
	free_string_to_id(stoi);
	
	free_ystate_to_id(ytoi);
	
	free_lstate_to_id(ltoi);
	
	free_dynvector(starts);
	free_dynvector(EOFs);
	free_dynvector(accepts);
	
	free_dyntable(lexer);
	free_dyntable(shifts);
	free_dyntable(reduces);
	free_dyntable(gotos);
	
	free_quack(yacc_todo);
	free_quack(lex_todo);
	
	EXIT;
}







