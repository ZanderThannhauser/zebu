
#include <debug.h>

#include <avl/avl.h>
#include <avl/new.h>

#include <cmdln/struct.h>
#include <cmdln/process.h>
#include <cmdln/free.h>

#include <lex/new.h>
#include <lex/free.h>

#include <parser/mains_parse.h>
#include <parser/options/new.h>
#include <parser/options/free.h>
#include <parser/scope/new.h>
#include <parser/scope/free.h>

#include <memory/arena/new.h>
#include <memory/arena/free.h>

#include <yacc/yacc.h>

/*#include <out/out.h>*/

int main(int argc, char* argv[])
{
	int error = 0;
	ENTER;
	
	struct cmdln* flags = cmdln_process(argc, argv);
	
	struct scope* scope = new_scope();
	
	struct options* options = new_options();
	
	struct memory_arena* scratchpad = new_memory_arena();
	
	struct lex* lex = new_lex(flags->debug.lex);
	
	mains_parse(options, scope, scratchpad, lex, flags->input_path);
	
	yacc();
	
	TODO;
	
	#if 0
	out(LRP, flags->output_path);
	
	free(LRP);
	
	free_lex(lex);
	#endif
	
	free_memory_arena(scratchpad);
	
	free_scope(scope);
	
	free_options(options);
	
	free_cmdln(flags);
	
	EXIT;
	return 0;
}










