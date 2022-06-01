
#include <debug.h>

#include <avl/avl.h>
#include <avl/new.h>

#include <cmdln/struct.h>
#include <cmdln/process.h>
#include <cmdln/free.h>

#include <lex/new.h>
#include <lex/free.h>

#include <parser/mains_parse.h>

#include <yacc/yacc.h>

#include <out/out.h>

int main(int argc, char* argv[])
{
	int error = 0;
	struct cmdln* flags = NULL;
	struct lex* lex = NULL;
	struct avl_tree_t* grammar = NULL;
	void* LRP = NULL;
	ENTER;
	
	error = 0
		?: cmdln_process(&flags, argc, argv)
		?: new_lex(&lex, flags->debug.lex)
		?: new_avl_tree(&grammar, NULL, NULL)
		?: mains_parse(grammar, flags->input_path, lex)
		?: yacc(&LRP, grammar, lex, flags->debug.yacc)
		?: out(LRP, flags->output_path)
		;
	
	free(LRP);
	avl_free_tree(grammar);
	free_lex(lex);
	free_cmdln(flags);
	
	EXIT;
	return 0;
}










