
enum parser_template
{
	pt_really_just_tables,
	
	pt_just_tables,
	
	pt_buffer_driven,
	
	pt_readline,
	
	pt_readline_debug,
	
	pt_fileio_debug,
	pt_fileio_passfail,
	pt_fileio_graphviz,
	
	number_of_parser_templates,
};

extern enum parser_template parser_template;

