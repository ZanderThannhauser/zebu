
#include <debug.h>

#include <cmdln/output_path.h>
#include <cmdln/output_prefix.h>

#include <set/yaccstate/new.h>
#include <set/yaccstate/add.h>
#include <set/yaccstate/free.h>

#include <set/lexstate/new.h>
#include <set/lexstate/add.h>
#include <set/lexstate/free.h>

#include <yacc/state/struct.h>

#include "dyntable/new.h"
#include "dyntable/set.h"
#include "dyntable/free.h"

#include "reducerule_to_id/new.h"
#include "reducerule_to_id/reducerule_to_id.h"
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
#include "unsignedset_to_id/free.h"

#include "dynvector/new.h"
#include "dynvector/set.h"
#include "dynvector/free.h"

#include "out.h"

#if 0
static struct {
	const char **source, **header;
} lookup[number_of_parser_templates] = {
	[pt_just_tables] = {&just_tables_source, &just_tables_header},
	[pt_buffer_driven] = {&buffer_driven_source, &buffer_driven_header},
	[pt_readline] = {&readline_source, &readline_header},
	[pt_readline_debug] = {&readline_debug_source, &readline_debug_header},
	[pt_fileio_debug] = {&fileio_debug_source, &fileio_debug_header},
	[pt_fileio_passfail] = {&fileio_passfail_source, &fileio_passfail_header},
	[pt_fileio_graphviz] = {&fileio_graphviz_source, &fileio_graphviz_header},
};
#endif

void out(struct yacc_state* start)
{
	ENTER;
	
	struct ystate_to_id* ytoi = new_ystate_to_id();
	
	struct lstate_to_id* ltoi = new_lstate_to_id();
	
	struct unsignedset_to_id* ustoi = new_unsignedset_to_id();
	
	struct string_to_id* stoi = new_string_to_id();
	
	struct reducerule_to_id* rrtoi = new_reducerule_to_id();
	
	struct dynvector* starts = new_dynvector("starts");
	
	struct dyntable* shifts = new_dyntable("shifts");
	
	struct dyntable* reduces = new_dyntable("reduces");
	
	struct dyntable* gotos = new_dyntable("gotos");
	
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
			
			unsigned rrid = reducerule_to_id(rrtoi, ele->reduce_as, ele->popcount, ele->reductioninfo);
			
			dyntable_set(reduces, yid, tid, rrid);
		}
	}
	
	while (quack_len(lex_todo))
	{
		TODO;
		#if 0
		unsigned lid = lstate_to_id(ltoi, state);
		
		dpv(lid);
		
		if (state->accepting)
		{
			unsigned tid = tokenset_to_id(ttoi, state->accepting);
			
			dpv(tid);
			
			dynvector_set(accepts, lid, tid);
		}
		
		for (unsigned i = 0, n = state->transitions.n; i < n; i++)
		{
			const struct ltransition* const ele = state->transitions.data[i];
			
			unsigned slid = lstate_to_id(ltoi, ele->to);
			
			fill_lex_tables(shared, ele->to);
			
			dyntable_set(lexer, lid, ele->value, slid);
		}
		
		if (state->default_transition_to)
		{
			unsigned slid = lstate_to_id(ltoi, state->default_transition_to);
			
			fill_lex_tables(shared, state->default_transition_to);
			
			dynvector_set(defaults, lid, slid);
		}
		
		if (state->EOF_transition_to)
		{
			unsigned slid = lstate_to_id(ltoi, state->EOF_transition_to);
			
			fill_lex_tables(shared, state->EOF_transition_to);
			
			dynvector_set(EOFs, lid, slid);
		}
		#endif
	}
	
	dpvs(output_path);
	dpvs(output_prefix);
	
	// build header:
	
	// {{PREFIX}}
	
	// {{SHIFT_TABLE}}
	
	// {{REDUCE_TABLE}}
	
	// {{GOTO_TABLE}}
	
	// {{PARSE_TREE_TYPES}}
	
	// {{PARSE_TREE_DESTRUCTORS}}
	
	// build source:
	// {{PREFIX}}
	
	// {{SHIFT_TABLE}}
	
	// {{REDUCE_TABLE}}
	
	// {{GOTO_TABLE}}
	
	// {{PARSE_TREE_TYPES}}
	
	// {{PARSE_TREE_CONSTRUCTORS}}
	
	// {{PARSE_TREE_GRAPHVIZ_PRINTOUT}}
	
	// {{PARSE_TREE_TERMINAL_PRINTOUT}}
	
	// {{PARSE_TREE_DESTRUCTORS}}
	
	// iterate through the template, looking for '{{' & '}}'
	// ifelses to switch over what the inner-string is
	// to write out the content
	TODO;
	
	free_reducerule_to_id(rrtoi);
	
	free_unsignedset_to_id(ustoi);
	
	free_yaccstateset(yacc_queued);
	
	free_lexstateset(lex_queued);
	
	free_string_to_id(stoi);
	
	free_ystate_to_id(ytoi);
	
	free_lstate_to_id(ltoi);
	
	free_dynvector(starts);
	
	free_dyntable(shifts);
	
	free_dyntable(reduces);
	
	free_dyntable(gotos);
	
	free_quack(yacc_todo);
	
	free_quack(lex_todo);
	
	EXIT;
}








	#if 0
	char path[PATH_MAX];
	
	FILE* source = NULL;
	FILE* header = NULL;
	
	struct out_shared* shared = malloc(sizeof(*shared));
	
	reduces = new_dyntable("reduces");
	popcounts = new_dyntable("popcounts");
	
	lexer = new_dyntable("lexer");
	
	defaults = new_dynvector("defaults");
	
	EOFs = new_dynvector("EOFs");
	
	accepts = new_dynvector("accepts");
	
	fill_yacc_tables(shared, start);
	
	strcat(strcpy(path, output_path), ".c");
	
	if (!(source = fopen(path, "w")))
	{
		fprintf(stderr, "%s: fopen(\"%s\", \"w\"): %m\n", argv0, path);
		exit(1);
	}
	
	strcat(strcpy(path, output_path), ".h");
	
	if (!(header = fopen(path, "w")))
	{
		fprintf(stderr, "%s: fopen(\"%s\", \"w\"): %m\n", argv0, path);
		exit(1);
	}
	
	dyntable_print_source(shifts, output_prefix, source, header);
	dyntable_print_source(reduces, output_prefix, source, header);
	dyntable_print_source(popcounts, output_prefix, source, header);
	dyntable_print_source(lexer, output_prefix, source, header);
	
	dynvector_print_source(starts, output_prefix, source, header);
	dynvector_print_source(defaults, output_prefix, source, header);
	dynvector_print_source(EOFs, output_prefix, source, header);
	dynvector_print_source(accepts, output_prefix, source, header);
	
	{
		unsigned sid = grammar_to_id(ttoi, "(start)");
		
		fprintf(source, "const unsigned start_grammar_id = %u;\n", sid);
		fprintf(header, "extern const unsigned start_grammar_id;\n");
	}
	
	tokenset_to_id_print_source(ttoi, output_prefix, source, header);
	
	if (parser_template != pt_nothing)
	{
		assert(lookup[parser_template].source);
		
		const char* template_source = *lookup[parser_template].source;
		const char* template_header = *lookup[parser_template].header;
		
		char* specialized_source = strfandr(template_source, "<PREFIX>", output_prefix);
		char* specialized_header = strfandr(template_header, "<PREFIX>", output_prefix);
		
		fputs(specialized_source, source);
		fputs(specialized_header, header);
		
		free(specialized_source);
		free(specialized_header);
	}
	
	free_ystate_to_id(ytoi);
	free_lstate_to_id(ltoi);
	free_tokenset_to_id(ttoi);

	free_dyntable(shifts);
	free_dyntable(reduces);
	free_dyntable(popcounts);
	free_dyntable(lexer);

	free_dynvector(starts);
	free_dynvector(defaults);
	free_dynvector(EOFs);
	free_dynvector(accepts);

	free(shared);
	
	fclose(source);
	fclose(header);
	#endif
	




