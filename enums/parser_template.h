
#ifndef ENUM_PARSER_TEMPLATE_H
#define ENUM_PARSER_TEMPLATE_H

enum parser_template
{
	pt_nothing,
	
	pt_just_tables,
	
	pt_buffer_driven,
	
	pt_readline,
	
	pt_readline_debug,
	
	pt_fileio_debug,
	pt_fileio_passfail,
	pt_fileio_graphviz,
	
	number_of_parser_templates,
};

#endif
