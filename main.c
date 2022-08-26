
#include <assert.h>
#include <signal.h>
#include <sys/time.h>
#include <stddef.h>

#include <debug.h>

#include <avl/alloc_tree.h>
#include <avl/free_tree.h>

#include <cmdln/struct.h>
#include <cmdln/process.h>
#include <cmdln/verbose.h>
#include <cmdln/free.h>

#include <lex/new.h>
#include <lex/process_disambiguatations.h>
#include <lex/free.h>

#include <misc/default_sighandler.h>

#include <named/grammar/compare.h>
#include <named/grammar/free.h>

#include <parser/mains_parse.h>

#include <parser/options/struct.h>
#include <parser/options/new.h>
#include <parser/options/free.h>

#include <arena/stdlib/new.h>
#include <arena/mmap/new.h>
#include <arena/free.h>

#include <yacc/yacc.h>
#include <yacc/state/free.h>

#include <out/out.h>

#ifdef VERBOSE
#include <stdio.h>
#endif

int main(int argc, char* argv[])
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct memory_arena* stdlib_arena = new_stdlib_arena();
	#endif
	
	#ifdef WITH_ARENAS
	struct cmdln* flags = cmdln_process(stdlib_arena, argc, argv);
	#else
	struct cmdln* flags = cmdln_process(argc, argv);
	#endif
	
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
	
	#ifdef WITH_ARENAS
	struct options* options = new_options(stdlib_arena);
	#else
	struct options* options = new_options();
	#endif
	
	#ifdef WITH_ARENAS
	struct memory_arena* token_arena = new_mmap_arena();
	struct memory_arena* grammar_arena = new_mmap_arena();
	#endif
	
	#ifdef WITH_ARENAS
	struct lex* lex = new_lex(token_arena);
	#else
	struct lex* lex = new_lex();
	#endif
	
	#ifdef WITH_ARENAS
	struct avl_tree_t* grammar = avl_alloc_tree(grammar_arena, compare_named_grammars, free_named_grammar);
	#else
	struct avl_tree_t* grammar = avl_alloc_tree(compare_named_grammars, free_named_grammar);
	#endif
	
	#ifdef WITH_ARENAS
	mains_parse(grammar_arena, token_arena, options, grammar, lex, flags->input_path);
	#else
	mains_parse(options, grammar, lex, flags->input_path);
	#endif
	
	if (options->disambiguatations.head)
		lex_process_disambiguatations(lex, options->disambiguatations.head);
	
	#ifdef WITH_ARENAS
	struct memory_arena* tokenizer_arena = new_mmap_arena();
	struct memory_arena* parser_arena = new_mmap_arena();
	#endif
	
	struct yacc_state* parser = yacc(
		#ifdef WITH_ARENAS
		grammar_arena, token_arena,
		tokenizer_arena, parser_arena,
		#endif
		lex, grammar);
	
	#ifdef WITH_ARENAS
	free_memory_arena(token_arena);
	free_memory_arena(grammar_arena);
	#else
	free_options(options);
	avl_free_tree(grammar);
	free_lex(lex);
	#endif
	
	out(parser, flags->output_path, flags->output_prefix, flags->parser_template);
	
	#ifdef VERBOSE
	if (verbose)
		fputs("\e[K", stdout);
	#endif
	
	#ifdef WITH_ARENAS
	free_memory_arena(tokenizer_arena);
	free_memory_arena(parser_arena);
	free_memory_arena(stdlib_arena);
	#else
	free_yacc_state(parser);
	free_cmdln(flags);
	#endif
	
	EXIT;
	return 0;
}










