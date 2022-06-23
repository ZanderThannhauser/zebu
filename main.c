
#include <debug.h>

#include <avl/avl.h>
#include <avl/new.h>

#include <cmdln/struct.h>
#include <cmdln/process.h>
#include <cmdln/free.h>

#include <lex/new.h>
#include <lex/free.h>

#include <parser/mains_parse.h>

/*#include <yacc/yacc.h>*/

/*#include <out/out.h>*/

int main(int argc, char* argv[])
{
	int error = 0;
	ENTER;
	
	struct cmdln* flags = cmdln_process(argc, argv);
	
	struct lex* lex = new_lex(flags->debug.lex);
	
	mains_parse(flags->input_path, lex);
	
	TODO;
	
	#if 0
	void* LRP = yacc(&LRP, grammar, lex, flags->debug.yacc);
	
	out(LRP, flags->output_path);
	
	free(LRP);
	
	avl_free_tree(grammar);
	
	free_lex(lex);
	#endif
	
	free_cmdln(flags);
	
	EXIT;
	return 0;
}










