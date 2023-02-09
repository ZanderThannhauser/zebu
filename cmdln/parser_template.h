
enum parser_template
{
	pt_really_just_tables,
	
	pt_just_tables,
	
	pt_charbuffer,
	pt_piecewise_charbuffer,
	
	pt_readline,
	pt_readline_with_driver,
	
	pt_fileio,
	pt_fileio_with_driver,
	
	pt_myreadline_with_driver,
	
	number_of_parser_templates,
};

extern enum parser_template parser_template;

