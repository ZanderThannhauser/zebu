
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

#include "output.h"

int main()
{
	for (char* line; (line = readline(">>> "));)
	{
		struct zebu_state* new = new_zebu_state();
		
		zebu_parse(new, (unsigned char*) line, strlen(line));
		
		zebu_parse_EOF(new);
		
		puts("accepted!");
		
		add_history(line);
		free_zebu_state(new);
		free(line);
	}
	
	return 0;
}

