
#include <assert.h>
#include <debug.h>

#include <avl/avl.h>
#include <avl/new.h>

#include <cmdln/struct.h>
#include <cmdln/process.h>
#include <cmdln/free.h>

#include <lex/new.h>
#include <lex/free.h>

#include <parser/mains_parse.h>
#include <parser/options/struct.h>
#include <parser/options/new.h>
#include <parser/options/free.h>
#include <parser/scope/struct.h>
#include <parser/scope/new.h>
#include <parser/scope/free.h>

#include <memory/arena/new.h>
#include <memory/arena/free.h>

#include <yacc/yacc.h>

#include <out/out.h>

int main(int argc, char* argv[])
{
	ENTER;
	
	struct cmdln* flags = cmdln_process(argc, argv);
	
	struct memory_arena* scratchpad = new_memory_arena();
	
	struct scope* scope = new_scope();
	
	struct options* options = new_options();
	
	struct lex* lex = new_lex(flags->debug.lex);
	
	mains_parse(options, scope, scratchpad, lex, flags->input_path);
	
	struct yacc_state* parser = yacc(lex, scope->grammar, scratchpad);
	
	out(parser, flags->output_prefix, flags->just_output_tables);
	
	free_lex(lex);
	
	free_scope(scope);
	
	free_memory_arena(scratchpad);
	
	free_options(options);
	
	free_cmdln(flags);
	
	EXIT;
	return 0;
}










