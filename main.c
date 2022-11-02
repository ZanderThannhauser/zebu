
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

#include <named/structinfo/compare.h>
#include <named/structinfo/free.h>

#include <named/gegex/compare.h>
#include <named/gegex/free.h>

#include <parser/main_parse.h>

#include <yacc/yacc.h>

#include <out/out.h>

#include <yacc/state/free.h>

#ifdef VERBOSE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef WINDOWS_PLATFORM
#include <compat/timer_thread.h>
#endif
#endif

#ifdef DOTOUT
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

#include <enums/error.h>
#endif

int main(int argc, char* argv[])
{
	ENTER;
	
	cmdln_process(argc, argv);
	
	#ifdef VERBOSE
	if (verbose)
	{
		#ifdef LINUX_PLATFORM
		signal(SIGALRM, default_sighandler);
		
		setitimer(ITIMER_REAL, &(const struct itimerval) {
			.it_interval = {.tv_sec = 0, .tv_usec = 250 * 1000},
			.it_value = {.tv_sec = 1, .tv_usec = 0},
		}, NULL);
		#else
		#ifdef WINDOWS_PLATFORM
		timer_handler = default_sighandler;
		start_timer_thread();
		#else
		#error bad platform
		#endif
		#endif
	}
	#endif
	
	#ifdef DOTOUT
	#ifdef LINUX_PLATFORM
	if (mkdir("dot", 0775) < 0 && errno != EEXIST)
	#else
	#ifdef WINDOWS_PLATFORM
	if (mkdir("dot") < 0 && errno != EEXIST)
	#else
	#error bad platform
	#endif
	#endif
	{
		fprintf(stderr, "zebu: mkdir(\"dot\"): %m\n");
		exit(e_syscall_failed);
	}
	#endif
	
	struct lex* lex = new_lex();
	
	struct avl_tree_t* grammar = avl_alloc_tree(compare_named_gegexes, free_named_gegex);
	
	struct avl_tree_t* extra_fields = avl_alloc_tree(compare_named_structinfos, free_named_structinfo);
	
	main_parse(grammar, extra_fields, lex);
	
	struct yacc_state* parser = yacc(lex, grammar, extra_fields);
	
	out(parser);
	
	#ifdef VERBOSE
	void handler(int _)
	{
		char ptr[100] = {};
		
		size_t len = snprintf(ptr, 100, "\e[K" "zebu: freeing data structures ...\r");
		
		if (write(1, ptr, len) != len)
		{
			abort();
		}
	}
	
	#ifdef LINUX_PLATFORM
	signal(SIGALRM, handler);
	#else
	#ifdef WINDOWS_PLATFORM
	timer_handler = handler;
	#else
	#error bad platform
	#endif
	#endif
	#endif
	
	free_yacc_state(parser);
	
	avl_free_tree(extra_fields);
	
	avl_free_tree(grammar);
	
	free_lex(lex);
	
	#ifdef VERBOSE
	#ifdef WINDOWS_PLATFORM
	join_timer_thread();
	#endif
	if (verbose && write(1, "\e[K", 3) < 3)
		abort();
	#endif
	
	EXIT;
	return 0;
}




























