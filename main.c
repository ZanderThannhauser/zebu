
#include <assert.h>
#include <signal.h>
#include <sys/time.h>
#include <stddef.h>

#include <debug.h>

#include <avl/alloc_tree.h>
/*#include <avl/free_tree.h>*/

#include <cmdln/struct.h>
#include <cmdln/process.h>
#include <cmdln/verbose.h>

#include <lex/new.h>
/*#include <lex/add_EOF_token.h>*/
/*#include <lex/process_disambiguatations.h>*/
/*#include <lex/free.h>*/

#include <misc/default_sighandler.h>

#include <named/grammar/compare.h>
#include <named/grammar/free.h>

#include <parser/mains_parse.h>

#include <parser/options/struct.h>
#include <parser/options/new.h>
/*#include <parser/options/free.h>*/

#include <arena/stdlib/new.h>
#include <arena/mmap/new.h>
#include <arena/free.h>

#include <yacc/yacc.h>

#include <out/out.h>

#ifdef RELEASE
/*#include <signal.h>*/
/*#include <sys/time.h>*/

/*#include <cmdln/verbose.h>*/

/*#include <misc/default_sighandler.h>*/
#endif

int main(int argc, char* argv[])
{
	ENTER;
	
	struct memory_arena* stdlib_arena = new_stdlib_arena();
	
	struct cmdln* flags = cmdln_process(stdlib_arena, argc, argv);
	
	#ifdef RELEASE
	if (verbose)
	{
		signal(SIGALRM, default_sighandler);
		
		setitimer(ITIMER_REAL, &(const struct itimerval) {
			.it_interval = {.tv_sec = 0, .tv_usec = 500 * 1000},
			.it_value = {.tv_sec = 0, .tv_usec = 500 * 1000},
		}, NULL);
	}
	#endif
	
	struct options* options = new_options(stdlib_arena);
	
	struct memory_arena* token_arena = new_mmap_arena();
	
	struct lex* lex = new_lex(token_arena);
	
	struct memory_arena* grammar_arena = new_mmap_arena();
	
	struct avl_tree_t* grammar = avl_alloc_tree(grammar_arena, compare_named_grammars, NULL);
	
	mains_parse(grammar_arena, token_arena, options, grammar, lex, flags->input_path);
	
	if (options->disambiguatations.head)
	{
		TODO;
		#if 0
		lex_process_disambiguatations(lex, options->disambiguatations.head);
		#endif
	}
	
	struct memory_arena* tokenizer_arena = new_mmap_arena();
	
	struct memory_arena* parser_arena = new_mmap_arena();
	
	struct yacc_state* parser = yacc(
		grammar_arena, token_arena,
		tokenizer_arena, parser_arena,
		lex, grammar,
		flags->simplify_tokenizer);
	
	free_memory_arena(token_arena);
	free_memory_arena(grammar_arena);
	
	out(parser,
		flags->output_path,
		flags->output_prefix,
		flags->parser_template);
	
	free_memory_arena(tokenizer_arena);
	free_memory_arena(parser_arena);
	free_memory_arena(stdlib_arena);
	
	EXIT;
	return 0;
}










