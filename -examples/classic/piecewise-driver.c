
#include <stdio.h>

#include "classic.h"

int main()
{
	puts("hello, world!");
	
	struct zebu_state* state = new_zebu_state();
	
	{
		zebu_parse(state, (void*) "aab", 3);
		
		zebu_parse(state, (void*) "bcc::x!", 7);
		
		struct zebu_$start* root = zebu_close(state);
		
		free_zebu_$start(root);
	}
	
	zebu_reset(state);
	
	{
		zebu_parse(state, (void*) "abcc :", 6);
		
		zebu_parse(state, (void*) "wxy .", 5);
		
		struct zebu_$start* root = zebu_close(state);
		
		free_zebu_$start(root);
	}
	
	free_zebu_state(state);
	
	return 0;
}

