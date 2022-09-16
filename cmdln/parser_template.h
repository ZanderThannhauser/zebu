
enum parser_template
{
	pt_really_just_tables,
	
	pt_just_tables,
	
/*	pt_function_debug,*/
/*	pt_function_passfail,*/
	
	pt_readline,
	pt_readline_debug,
	pt_readline_with_driver,
	pt_readline_with_driver_debug,
/*	pt_readline_passfail,*/
	
	pt_fileio_with_driver_debug,
	pt_fileio_with_driver,
/*	pt_fileio_passfail_debug,*/
/*	pt_fileio_passfail,*/
/*	pt_fileio_graphviz,*/
	
	number_of_parser_templates,
};

extern enum parser_template parser_template;

