
#include <string.h>

#include <memory/smalloc.h>

#include <linux/limits.h>

#include <debug.h>

#include <stdlib.h>

#include <defines/argv0.h>

#include <misc/phase_counter.h>

#include "ystate_to_id/new.h"
#include "ystate_to_id/free.h"

#include "lstate_to_id/new.h"
#include "lstate_to_id/free.h"

#include "tokenset_to_id/new.h"
#include "tokenset_to_id/free.h"

#include "grammar_to_id/new.h"
#include "grammar_to_id/print_source.h"
#include "grammar_to_id/print_header.h"
#include "grammar_to_id/free.h"

#include "dyntable/new.h"
#include "dyntable/print_source.h"
#include "dyntable/print_header.h"
#include "dyntable/free.h"

#include "dynvector/new.h"
#include "dynvector/print_source.h"
#include "dynvector/print_header.h"
#include "dynvector/free.h"

#include "shared.h"
#include "fill_yacc_tables.h"
#include "out.h"

void out(
	struct yacc_state* start,
	const char* output_prefix,
	bool just_output_tables)
{
	ENTER;
	
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
	
	shared->starts = new_dynvector("starts");
	shared->defaults = new_dynvector("defaults");
	shared->accepts = new_dynvector("accepts");
	
	phase_counter++;
	
	fill_yacc_tables(shared, start);
	
	strcat(strcpy(path, output_prefix), ".c");
	
	if (!(source = fopen(path, "w")))
	{
		fprintf(stderr, "%s: fopen(\"%s\", \"w\"): %m\n", argv0, path);
		exit(1);
	}
	
	strcat(strcpy(path, output_prefix), ".h");
	
	if (!(header = fopen(path, "w")))
	{
		fprintf(stderr, "%s: fopen(\"%s\", \"w\"): %m\n", argv0, path);
		exit(1);
	}
	
	dyntable_print_source(shared->shifts, source, header);
	dyntable_print_source(shared->reduces, source, header);
	dyntable_print_source(shared->lexer, source, header);
	
	dynvector_print_source(shared->starts, source, header);
	dynvector_print_source(shared->defaults, source, header);
	dynvector_print_source(shared->accepts, source, header);
	
	#if 0
	fprintf(source, "#ifdef DEBUGGING\n");
	grammar_to_id_print_source(shared->gtoi, source);
	fprintf(source, "#endif // DEBUGGING\n");
	
	fprintf(header, "#ifdef DEBUGGING\n");
	grammar_to_id_print_header(shared->gtoi, header);
	fprintf(header, "#endif // DEBUGGING\n");
	#endif
	
	if (!just_output_tables)
	{
		HERE;
	}
	
	free_ystate_to_id(shared->ytoi);
	free_lstate_to_id(shared->ltoi);
	free_tokenset_to_id(shared->ttoi);
	
	free_dyntable(shared->shifts);
	free_dyntable(shared->reduces);
	free_dyntable(shared->lexer);
	
	free_dynvector(shared->starts);
	free_dynvector(shared->defaults);
	free_dynvector(shared->accepts);
	
	free(shared);
	
	fclose(source);
	fclose(header);
	
	EXIT;
}












