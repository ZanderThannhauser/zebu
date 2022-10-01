
enum parser_template
{
	pt_really_just_tables,
	
	pt_just_tables,
	
	pt_charbuffer,
	pt_charbuffer_piecewise,
	
	pt_readline,
	pt_readline_with_driver,
	
	pt_fileio,
	pt_fileio_with_driver,
	
	number_of_parser_templates,
};

extern enum parser_template parser_template;

