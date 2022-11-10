
#ifndef ERROR_ENUM
#define ERROR_ENUM

enum
{
	e_success,
	e_syscall_failed,
	e_bad_cmdline_args,
	e_out_of_memory,
	e_bad_input_file,
	e_syntax_error,
	e_shift_reduce_error,
	e_reduce_reduce_error,
	
	number_of_errors,
};

#endif
