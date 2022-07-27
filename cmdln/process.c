
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>
#include <debug.h>

#include <defines/argv0.h>

#include <macros/strequals.h>

#include <enums/error.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "usage.h"
#include "process.h"

struct cmdln* cmdln_process(int argc, char* argv[])
{
	ENTER;
	
	const char* input_path = NULL;
	const char* output_path = NULL;
	
	const char* output_prefix = "zebu";
	
	bool debug_lex = false;
	bool debug_yacc = false;
	bool paste_parser_code = true;
	bool verbose = false;
	
	int opt, option_index;
	const struct option long_options[] = {
		{"input",  required_argument, 0, 'i'},
		{"output",       no_argument, 0, 'o'},
		{"debug",  required_argument, 0, 'd'},
		{"verbose",      no_argument, 0, 'v'},
		{"help",         no_argument, 0, 'h'},
		{ 0,                       0, 0,  0 },
	};
	
	while ((opt = getopt_long(argc, argv, "i:" "o:" "p" "M" "d:" "v" "h",
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
			
			case 'd':
				if (strequals(optarg, "lex")) {
					debug_lex = true;
				} else if (strequals(optarg, "yacc")) {
					debug_yacc = true;
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
	
	struct cmdln* flags = smalloc(sizeof(*flags));
	
	flags->input_path = input_path;
	flags->output_path = output_path;
	flags->output_prefix = output_prefix;
	
	flags->debug.lex = debug_lex;
	flags->debug.yacc = debug_yacc;
	
	flags->paste_parser_code = paste_parser_code;
	
	flags->verbose = verbose;
	
	dpvs(flags->input_path);
	dpvs(flags->output_path);
	dpvs(flags->output_prefix);
	
	dpvb(flags->debug.lex);
	dpvb(flags->debug.yacc);
	dpvb(flags->paste_parser_code);
	dpvb(flags->verbose);
		
	EXIT;
	return flags;
}
















