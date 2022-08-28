
#if 0
#include <assert.h>
#include <string.h>

#include <linux/limits.h>

#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>
#include <arena/dealloc.h>

#include <defines/argv0.h>

/*#include <defines/argv0.h>*/

#include <misc/strfandr.h>

/*#include <set/of_tokens/foreach.h>*/
/*#include <set/of_tokens/is_disjoint.h>*/

/*#include <set/of_strs/foreach.h>*/

/*#include <named/grammar/struct.h>*/

/*#include <yacc/shared/struct.h>*/
/*#include <yacc/get_deps.h>*/
/*#include <yacc/lookup_tokenset.h>*/

#include <arena/mmap/new.h>
#include <arena/free.h>

#include <misc/phase_counters.h>

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

#include "escaped/just_tables_source.h"
#include "escaped/just_tables_header.h"

#include "escaped/buffer_driven_source.h"
#include "escaped/buffer_driven_header.h"

#include "escaped/readline_source.h"
#include "escaped/readline_header.h"

#include "escaped/readline_debug_source.h"
#include "escaped/readline_debug_header.h"

#include "escaped/fileio_debug_source.h"
#include "escaped/fileio_debug_header.h"

#include "escaped/fileio_passfail_source.h"
#include "escaped/fileio_passfail_header.h"

#include "escaped/fileio_graphviz_source.h"
#include "escaped/fileio_graphviz_header.h"

#include "shared.h"
#include "fill_yacc_tables.h"
#include "out.h"

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

void out(
	struct yacc_state* start,
	const char* output_path,
	const char* output_prefix,
	enum parser_template parser_template)
{
	ENTER;
	
	char path[PATH_MAX];
	
	FILE* source = NULL;
	FILE* header = NULL;
	
	#ifdef WITH_ARENAS
	struct memory_arena* out_arena = new_mmap_arena();
	
	struct out_shared* shared = arena_malloc(out_arena, sizeof(*shared));
	#else
	struct out_shared* shared = malloc(sizeof(*shared));
	#endif
	
	#ifdef WITH_ARENAS
	shared->ytoi = new_ystate_to_id(out_arena);
	shared->ltoi = new_lstate_to_id(out_arena);
	shared->ttoi = new_tokenset_to_id(out_arena);
	#else
	shared->ytoi = new_ystate_to_id();
	shared->ltoi = new_lstate_to_id();
	shared->ttoi = new_tokenset_to_id();
	#endif
	
	#ifdef WITH_ARENAS
	shared->shifts = new_dyntable(out_arena, "shifts");
	shared->reduces = new_dyntable(out_arena, "reduces");
	shared->popcounts = new_dyntable(out_arena, "popcounts");
	shared->lexer = new_dyntable(out_arena, "lexer");
	#else
	shared->shifts = new_dyntable("shifts");
	shared->reduces = new_dyntable("reduces");
	shared->popcounts = new_dyntable("popcounts");
	shared->lexer = new_dyntable("lexer");
	#endif
	
	#ifdef WITH_ARENAS
	shared->starts = new_dynvector(out_arena, "starts");
	shared->defaults = new_dynvector(out_arena, "defaults");
	shared->EOFs = new_dynvector(out_arena, "EOFs");
	shared->accepts = new_dynvector(out_arena, "accepts");
	#else
	shared->starts = new_dynvector("starts");
	shared->defaults = new_dynvector("defaults");
	shared->EOFs = new_dynvector("EOFs");
	shared->accepts = new_dynvector("accepts");
	#endif
	
	yacc_phase_counter++;
	lex_phase_counter++;
	
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
	
	dyntable_print_source(shared->shifts, output_prefix, source, header);
	dyntable_print_source(shared->reduces, output_prefix, source, header);
	dyntable_print_source(shared->popcounts, output_prefix, source, header);
	dyntable_print_source(shared->lexer, output_prefix, source, header);
	
	dynvector_print_source(shared->starts, output_prefix, source, header);
	dynvector_print_source(shared->defaults, output_prefix, source, header);
	dynvector_print_source(shared->EOFs, output_prefix, source, header);
	dynvector_print_source(shared->accepts, output_prefix, source, header);
	
	{
		unsigned sid = grammar_to_id(shared->ttoi, "(start)");
		
		fprintf(source, "const unsigned start_grammar_id = %u;\n", sid);
		fprintf(header, "extern const unsigned start_grammar_id;\n");
	}
	
	tokenset_to_id_print_source(shared->ttoi, output_prefix, source, header);
	
	if (parser_template != pt_nothing)
	{
		assert(lookup[parser_template].source);
		
		const char* template_source = *lookup[parser_template].source;
		const char* template_header = *lookup[parser_template].header;
		
		#ifdef WITH_ARENAS
		char* specialized_source = strfandr(out_arena, template_source, "<PREFIX>", output_prefix);
		char* specialized_header = strfandr(out_arena, template_header, "<PREFIX>", output_prefix);
		#else
		char* specialized_source = strfandr(template_source, "<PREFIX>", output_prefix);
		char* specialized_header = strfandr(template_header, "<PREFIX>", output_prefix);
		#endif
		
		fputs(specialized_source, source);
		fputs(specialized_header, header);
		
		#ifdef WITH_ARENAS
		arena_dealloc(out_arena, specialized_source);
		arena_dealloc(out_arena, specialized_header);
		#else
		free(specialized_source);
		free(specialized_header);
		#endif
	}
	
	#ifdef WITH_ARENAS
	
	free_memory_arena(out_arena);
	
	#else

	free_ystate_to_id(shared->ytoi);
	free_lstate_to_id(shared->ltoi);
	free_tokenset_to_id(shared->ttoi);

	free_dyntable(shared->shifts);
	free_dyntable(shared->reduces);
	free_dyntable(shared->popcounts);
	free_dyntable(shared->lexer);

	free_dynvector(shared->starts);
	free_dynvector(shared->defaults);
	free_dynvector(shared->EOFs);
	free_dynvector(shared->accepts);

	free(shared);
	
	#endif
	
	fclose(source);
	fclose(header);
	
	EXIT;
}











#endif
