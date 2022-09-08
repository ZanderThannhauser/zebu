
#include <assert.h>
#include <signal.h>
#include <sys/time.h>
#include <stddef.h>

#include <debug.h>

#include <cmdln/process.h>
#include <cmdln/verbose.h>

#include <misc/default_sighandler.h>

#include <lex/new.h>
#include <lex/free.h>

#include <avl/alloc_tree.h>
#include <avl/free_tree.h>

#include <named/gegex/compare.h>
#include <named/gegex/free.h>

#include <parser/main_parse.h>

#include <yacc/yacc.h>

#include <out/out.h>

#include <yacc/state/free.h>

int main(int argc, char* argv[])
{
	ENTER;
	
	cmdln_process(argc, argv);
	
	#ifdef VERBOSE
	if (verbose)
	{
		signal(SIGALRM, default_sighandler);
		
		setitimer(ITIMER_REAL, &(const struct itimerval) {
			.it_interval = {.tv_sec = 0, .tv_usec = 500 * 1000},
			.it_value = {.tv_sec = 0, .tv_usec = 500 * 1000},
		}, NULL);
	}
	#endif
	
	#ifdef DOTOUT
	if (mkdir("dot", 0775) < 0 && errno != EEXIST)
	{
		fprintf(stderr, "zebu: mkdir(\"dot\"): %m\n");
		exit(e_syscall_failed);
	}
	#endif
	
	struct lex* lex = new_lex();
	
	struct avl_tree_t* grammar = avl_alloc_tree(compare_named_gegexes, free_named_gegex);
	
	main_parse(grammar, lex);
	
	struct yacc_state* parser = yacc(lex, grammar);
	
	out(parser);
	
<<<<<<< HEAD
	struct yacc_state* parser = yacc(
		#ifdef WITH_ARENAS
		grammar_arena, token_arena,
		tokenizer_arena, parser_arena,
		#endif
		lex, grammar);
=======
	free_yacc_state(parser);
>>>>>>> dev
	
	avl_free_tree(grammar);
	
	free_lex(lex);
	
	#ifdef VERBOSE
	if (verbose && write(1, "\e[K", 3) < 3)
		abort();
	#endif
	
	EXIT;
	return 0;
}









