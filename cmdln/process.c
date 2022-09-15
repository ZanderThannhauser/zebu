
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>
#include <sys/time.h>

#include <debug.h>

#include <macros/strequals.h>

#include <enums/error.h>

#include "usage.h"
#include "verbose.h"
#include "input_path.h"
#include "output_path.h"
#include "output_prefix.h"
#include "parser_template.h"
#include "minimize_lexer.h"
#include "process.h"

void cmdln_process(int argc, char* const* argv)
{
	ENTER;
	
	int opt, option_index;
	const struct option long_options[] = {
		{"input",    required_argument, 0, 'i'},
		{"output",         no_argument, 0, 'o'},
		{"prefix",   required_argument, 0, 'p'},
		{"template", required_argument, 0, 't'},
		{"minimize-lexer", no_argument, 0, 'l'},
		{"verbose",        no_argument, 0, 'v'},
		{"help",           no_argument, 0, 'h'},
		{ 0,                            0, 0,  0 },
	};
	
	while ((opt = getopt_long(argc, argv, "i:" "o:" "p" "t:" "l" "v" "h",
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
			
			case 't':
				if (strequals(optarg, "really-just-tables")) {
					parser_template = pt_really_just_tables;
				} else if (strequals(optarg, "just-tables")) {
					parser_template = pt_just_tables;
/*				} else if (strequals(optarg, "buffer-driven")) {*/
/*					parser_template = pt_buffer_driven;*/
				} else if (strequals(optarg, "readline")) {
					parser_template = pt_readline;
				} else if (strequals(optarg, "readline-debug")) {
					parser_template = pt_readline_debug;
				} else if (strequals(optarg, "readline-with-driver")) {
					parser_template = pt_readline_with_driver;
				} else if (strequals(optarg, "readline-with-driver-debug")) {
					parser_template = pt_readline_with_driver_debug;
				} else if (strequals(optarg, "fileio-debug")) {
					parser_template = pt_fileio_debug;
				} else if (strequals(optarg, "fileio")) {
					parser_template = pt_fileio;
/*				} else if (strequals(optarg, "fileio-passfail")) {*/
/*					parser_template = pt_fileio_passfail;*/
/*				} else if (strequals(optarg, "fileio-graphviz")) {*/
/*					parser_template = pt_fileio_graphviz;*/
				} else {
					usage(e_bad_cmdline_args);
				}
				break;
			
			case 'l':
				minimize_lexer = true;
				break;
			
			case 'v':
				#ifdef VERBOSE
				verbose = true;
				#endif
				break;
			
			case 'h':
				usage(0);
				break;
			
			default:
				usage(e_bad_cmdline_args);
				break;
		}
	}
	
	if (!input_path || !output_path)
	{
		fprintf(stderr, "zebu: missing arguments!\n");
		usage(e_bad_cmdline_args);
	}
	
	dpvs(input_path);
	dpvs(output_path);
	dpvs(output_prefix);
	
	EXIT;
}
















