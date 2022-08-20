
#include <assert.h>
#include <debug.h>

#include <avl/avl.h>
#include <avl/new.h>

#include <cmdln/struct.h>
#include <cmdln/process.h>
#include <cmdln/free.h>

#include <lex/new.h>
#include <lex/add_EOF_token.h>
#include <lex/process_disambiguatations.h>
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

#ifdef RELEASE
#include <signal.h>
#include <sys/time.h>

#include <cmdln/verbose.h>

#include <misc/default_sighandler.h>
#endif

int main(int argc, char* argv[])
{
	ENTER;
	
	struct cmdln* flags = cmdln_process(argc, argv);
	
	#ifdef RELEASE
	
	if (verbose)
	{
		signal(SIGALRM, default_sighandler);
		
		setitimer(ITIMER_REAL, &(const struct itimerval) {
			.it_interval = {.tv_sec = 0, .tv_usec = 100 * 1000},
			.it_value = {.tv_sec = 0, .tv_usec = 100 * 1000},
		}, NULL);
	}
	
	#endif
	
	struct memory_arena* scratchpad = new_memory_arena();
	
	struct scope* scope = new_scope();
	
	struct options* options = new_options();
	
	struct lex* lex = new_lex(scratchpad);
	
	mains_parse(options, scope, scratchpad, lex, flags->input_path);
	
	lex_add_EOF_token(lex, options->skip);
	
	if (options->disambiguatations.head)
	{
		lex_process_disambiguatations(lex, options->disambiguatations.head);
	}
	
	struct yacc_state* parser = yacc(lex, scope->grammar, scratchpad);
	
	out(parser,
		flags->output_path,
		flags->output_prefix,
		flags->parser_template);
	
	free_lex(lex);
	
	free_scope(scope);
	
	free_options(options);
	
	free_memory_arena(scratchpad);
	
	free_cmdln(flags);
	
	EXIT;
	return 0;
}










