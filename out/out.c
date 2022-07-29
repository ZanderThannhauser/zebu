
#include <assert.h>

#include <string.h>

#include <avl/foreach.h>

#include <memory/smalloc.h>

#include <linux/limits.h>

#include <debug.h>

#include <stdlib.h>

#include <defines/argv0.h>

#include <misc/strfandr.h>

#include <set/of_tokens/foreach.h>
#include <set/of_tokens/is_disjoint.h>

#include <set/of_strs/foreach.h>

#include <named/grammar/struct.h>

#include <yacc/shared/struct.h>
#include <yacc/get_deps.h>
#include <yacc/lookup_tokenset.h>

#include <yacc/phase_counter.h>
#include <lex/phase_counter.h>

#include "ystate_to_id/new.h"
#include "ystate_to_id/free.h"

#include "lstate_to_id/new.h"
#include "lstate_to_id/free.h"

#include "tokenset_to_id/new.h"
#include "tokenset_to_id/grammar_to_id.h"
#include "tokenset_to_id/print_source.h"
#include "tokenset_to_id/foreach.h"
#include "tokenset_to_id/free.h"

#include "dyntable/new.h"
#include "dyntable/set.h"
#include "dyntable/print_source.h"
#include "dyntable/free.h"

#include "dynvector/new.h"
#include "dynvector/print_source.h"
#include "dynvector/free.h"

#include "shared.h"
#include "parser_code.h"
#include "fill_yacc_tables.h"
#include "out.h"

void out(
	struct yacc_state* start,
	struct yacc_shared* yshared,
	const char* output_path,
	const char* output_prefix,
	bool paste_parser_code,
	bool yacc_debugging)
{
	ENTER;
	
	dpvb(paste_parser_code);
	
	char path[PATH_MAX];
	
	FILE* source = NULL;
	FILE* header = NULL;
	
	struct out_shared* shared = smalloc(sizeof(*shared));
	
	shared->ytoi = new_ystate_to_id();
	shared->ltoi = new_lstate_to_id();
	shared->ttoi = new_tokenset_to_id();
	
	shared->shifts = new_dyntable("shifts");
	shared->reduces = new_dyntable("reduces");
	shared->lexer = new_dyntable("lexer");
	shared->firsts = new_dyntable("firsts");
	
	shared->starts = new_dynvector("starts");
	shared->defaults = new_dynvector("defaults");
	shared->EOFs = new_dynvector("EOFs");
	shared->accepts = new_dynvector("accepts");
	
	yacc_phase_counter++;
	lex_phase_counter++;
	
	fill_yacc_tables(shared, start);
	
	avl_tree_foreach(yshared->grammar, ({
		void run (const void* item) {
			const struct named_grammar* ng = item;
			
			dpvs(ng->name);
			
			unsigned gid = grammar_to_id(shared->ttoi, ng->name);
			
			dpv(gid);
			
			struct tokenset* ft = lookup_tokenset(yshared->firsts.sets, ng->name);
				
			struct strset* fg = get_deps(yshared->firsts.dependant_on, ng->name);
			
			tokenset_to_id_foreach(shared->ttoi, ({
				void per_tokenset(const struct tokenset* ts, unsigned id) {
					if (!tokenset_is_disjoint(ts, ft))
						dyntable_set(shared->firsts, gid, id, true);
				}
				per_tokenset;
			}));
			
			strset_foreach(fg, ({
				void per_grammar(const char* grammar) {
					dpvs(grammar);
					
					unsigned sgid = grammar_to_id(shared->ttoi, grammar);
					
					dpv(sgid);
					
					dyntable_set(shared->firsts, gid, sgid, true);
				}
				per_grammar;
			}));
		}
		run;
	}));
	
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
	
	dyntable_print_source(shared->shifts, output_prefix, source, header);
	dyntable_print_source(shared->reduces, output_prefix, source, header);
	dyntable_print_source(shared->lexer, output_prefix, source, header);
	dyntable_print_source(shared->firsts, output_prefix, source, header);
	
	dynvector_print_source(shared->starts, output_prefix, source, header);
	dynvector_print_source(shared->defaults, output_prefix, source, header);
	dynvector_print_source(shared->EOFs, output_prefix, source, header);
	dynvector_print_source(shared->accepts, output_prefix, source, header);
	
	if (yacc_debugging)
		tokenset_to_id_print_source(shared->ttoi, output_prefix, source, header);
	
	if (paste_parser_code)
	{
		char* specialized_source = strfandr(yacc_debugging ? parser_debug : parser_code, "<PREFIX>", output_prefix);
		char* specialized_header = strfandr(parser_header, "<PREFIX>", output_prefix);
		
		fputs(specialized_source, source);
		fputs(specialized_header, header);
		
		free(specialized_source);
		free(specialized_header);
	}
	
	free_ystate_to_id(shared->ytoi);
	free_lstate_to_id(shared->ltoi);
	free_tokenset_to_id(shared->ttoi);
	
	free_dyntable(shared->shifts);
	free_dyntable(shared->reduces);
	free_dyntable(shared->lexer);
	free_dyntable(shared->firsts);
	
	free_dynvector(shared->starts);
	free_dynvector(shared->defaults);
	free_dynvector(shared->EOFs);
	free_dynvector(shared->accepts);
	
	free(shared);
	
	fclose(source);
	fclose(header);
	
	EXIT;
}












