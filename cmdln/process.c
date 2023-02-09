
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>
#include <sys/time.h>

#include <debug.h>

#include <macros/strequals.h>

#include <enums/error.h>

#ifdef WINDOWS_PLATFORM
#include <compat/stpcpy.h>
#endif

#include "usage.h"
#include "verbose.h"
#include "process.h"
#include "input_path.h"
#include "output_path.h"
#include "output_prefix.h"
#include "minimize_lexer.h"
#include "parser_template.h"
#include "make_dependencies.h"
#include "parser_program_name.h"
#include "make_dependencies_file.h"

void cmdln_process(int argc, char* const* argv)
{
	ENTER;
	
	int opt, option_index;
	const struct option long_options[] = {
		{"input",                  required_argument, 0, 'i'},
		{"output",                       no_argument, 0, 'o'},
		{"prefix",                 required_argument, 0, 'p'},
		{"template",               required_argument, 0, 't'},
		{"minimize-lexer",               no_argument, 0, 'm'},
		{"make-dependencies",            no_argument, 0, 'M'},
		{"make-dependencies-file", required_argument, 0, 'F'},
		{"program-name",           required_argument, 0, 'P'},
		{"verbose",                      no_argument, 0, 'v'},
		{"help",                         no_argument, 0, 'h'},
		{ 0,                                       0, 0,  0 },
	};
	
	while ((opt = getopt_long(argc, argv,
		"i:" "o:" "p:" "t:" "m" "M" "F:" "P:" "v" "h",
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
				} else if (strequals(optarg, "charbuffer")) {
					parser_template = pt_charbuffer;
				} else if (strequals(optarg, "piecewise-charbuffer")) {
					parser_template = pt_piecewise_charbuffer;
				} else if (strequals(optarg, "readline")) {
					parser_template = pt_readline;
				} else if (strequals(optarg, "readline-with-driver")) {
					parser_template = pt_readline_with_driver;
				} else if (strequals(optarg, "fileio")) {
					parser_template = pt_fileio;
				} else if (strequals(optarg, "fileio-with-driver")) {
					parser_template = pt_fileio_with_driver;
				} else if (strequals(optarg, "myreadline-with-driver")) {
					parser_template = pt_myreadline_with_driver;
				} else {
					fprintf(stderr, "zebu: '%s' is an invalid parser template!\n", optarg);
					usage(e_bad_cmdline_args);
				}
				break;
			
			case 'm':
				minimize_lexer = true;
				break;
			
			case 'M':
				make_dependencies = true;
				break;
			
			case 'F':
				make_dependencies = true;
				strcpy(make_dependencies_file, optarg);
				break;
			
			case 'P':
				stpcpy(stpcpy(stpcpy(parser_program_name, "\""), optarg), "\"");
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
			{
				fprintf(stderr, "zebu: unknown flag '%s'!\n", optarg);
				usage(e_bad_cmdline_args);
				break;
			}
		}
	}
	
	if (!input_path || !output_path)
	{
		fprintf(stderr, "zebu: missing arguments!\n");
		usage(e_bad_cmdline_args);
	}
	
	if (make_dependencies && !make_dependencies_file[0])
	{
		stpcpy(stpcpy(make_dependencies_file, output_path), ".d");
	}
	
	dpvs(input_path);
	dpvs(output_path);
	dpvs(output_prefix);
	
	EXIT;
}
















