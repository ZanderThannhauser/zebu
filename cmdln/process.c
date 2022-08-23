
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>
#include <sys/time.h>

#include <debug.h>

#include <defines/argv0.h>

#include <macros/strequals.h>

#include <enums/error.h>

#include <arena/malloc.h>

#include "struct.h"
#include "usage.h"
#include "verbose.h"
#include "process.h"

struct cmdln* cmdln_process(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	int argc, char* const* argv)
{
	ENTER;
	
	const char* input_path = NULL;
	const char* output_path = NULL;
	
	const char* output_prefix = "zebu";
	
	enum parser_template parser_template = pt_just_tables;
	
	bool simplify_tokenizer = false;
	
	int opt, option_index;
	const struct option long_options[] = {
		{"input",    required_argument, 0, 'i'},
		{"output",         no_argument, 0, 'o'},
		{"prefix",   required_argument, 0, 'p'},
		{"yacc",     required_argument, 0, 'y'},
		{"simplify", required_argument, 0, 's'},
		{"verbose",        no_argument, 0, 'v'},
		{"help",           no_argument, 0, 'h'},
		{ 0,                            0, 0,  0 },
	};
	
	while ((opt = getopt_long(argc, argv, "i:" "o:" "p" "y" "s" "M" "v" "h",
		long_options, &option_index)) >= 0)
	{
		switch (opt)
		{
			case 'i':
				input_path = optarg;
				break;
			
			case 'o':
				output_path = optarg;
				break;
			
			case 'p':
				output_prefix = optarg;
				break;
			
/*			case 'M':*/
/*				build_depends = true;*/
/*				break;*/
			
			case 'y':
				if (strequals(optarg, "really-just-tables")) {
					parser_template = pt_nothing;
				} else if (strequals(optarg, "just-tables")) {
					parser_template = pt_just_tables;
				} else if (strequals(optarg, "buffer-driven")) {
					parser_template = pt_buffer_driven;
				} else if (strequals(optarg, "readline")) {
					parser_template = pt_readline;
				} else if (strequals(optarg, "readline-debug")) {
					parser_template = pt_readline_debug;
				} else if (strequals(optarg, "fileio-debug")) {
					parser_template = pt_fileio_debug;
				} else if (strequals(optarg, "fileio-passfail")) {
					parser_template = pt_fileio_passfail;
				} else if (strequals(optarg, "fileio-graphviz")) {
					parser_template = pt_fileio_graphviz;
				} else {
					usage(e_bad_cmdline_args);
				}
				break;
			
			case 's':
				if (strequals(optarg, "tokenizer")) {
					simplify_tokenizer = true;
				} else {
					usage(e_bad_cmdline_args);
				}
				break;
			
			case 'v':
				verbose = true;
				break;
			
			case 'h':
				usage(0);
				break;
			
			default:
				usage(e_bad_cmdline_args);
				break;
		}
	}
	
	if (!input_path || !output_prefix)
	{
		fprintf(stderr, "%s: missing arguments!\n", argv0);
		usage(e_bad_cmdline_args);
	}
	
	#ifdef WITH_ARENAS
	struct cmdln* flags = arena_malloc(arena, sizeof(*flags));
	#else
	struct cmdln* flags = malloc(sizeof(*flags));
	#endif
	
	flags->input_path = input_path;
	flags->output_path = output_path;
	flags->output_prefix = output_prefix;
	
	flags->parser_template = parser_template;
	
	flags->simplify_tokenizer = simplify_tokenizer;
	
	dpvs(flags->input_path);
	dpvs(flags->output_path);
	dpvs(flags->output_prefix);
	
	dpv(flags->parser_template);
	
	dpvb(verbose);
	
	EXIT;
	return flags;
}
















