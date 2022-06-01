
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

int cmdln_process(struct cmdln** out, int argc, char* argv[])
{
	int error = 0;
	ENTER;
	
	const char* input_path = NULL;
	bool debug_lex = false;
	bool debug_yacc = false;
	bool verbose = false;
	
	int opt, option_index;
	const struct option long_options[] = {
		{"input",  required_argument, 0, 'i'},
		{"debug",  required_argument, 0, 'd'},
		{"verbose",      no_argument, 0, 'v'},
		{"help",         no_argument, 0, 'h'},
		{ 0,                       0, 0,  0 },
	};
	
	while (!error && (opt = getopt_long(argc, argv,
		"i:" "d:" "v" "h", long_options, &option_index)) >= 0)
	{
		switch (opt)
		{
			case 'i':
				input_path = optarg;
				break;
			
			case 'd':
				if (strequals(optarg, "lex")) {
					debug_lex = true;
				} else if (strequals(optarg, "yacc")) {
					debug_yacc = true;
				} else {
					error = e_bad_cmdline_args;
				}
				break;
			
			case 'v':
				verbose = true;
				break;
			
			case 'h':
			default:
				error = e_bad_cmdline_args;
				break;
		}
	}
	
	if (!error && !input_path)
	{
		fprintf(stderr, "%s: missing input file!\n", argv0);
		error = e_bad_cmdline_args;
	}
	
	if (error == e_bad_cmdline_args)
		usage();
	
	struct cmdln* flags = NULL;
	
	if (!error)
		error = smalloc((void**) &flags, sizeof(*flags));
	
	if (!error)
	{
		flags->input_path = input_path;
		
		flags->debug.lex = debug_lex;
		flags->debug.yacc = debug_yacc;
		
		flags->verbose = verbose;
		
		dpvs(flags->input_path);
		dpvb(flags->debug.lex);
		dpvb(flags->debug.yacc);
		dpvb(flags->verbose);
		
		*out = flags;
	}
	
	EXIT;
	return error;
}
















