
#include <stdarg.h>
#include <stdbool.h>
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "output.h"

static void check(const char* line, ...)
{
	struct zebu_state* state = new_zebu_state();
	
	{
		va_list va;
		
		va_start(va, line);
		
		printf("testing");
		const char* arg = line;
		do printf(" \"%s\"", arg);
		while ((arg = va_arg(va, char*)));
		
		puts("");
		
		va_end(va);
	}
	
	{
		va_list va;
		va_start(va, line);
		
		const char* arg = line;
		do zebu_parse(state, (void*) arg, strlen(line));
		while ((arg = va_arg(va, char*)));
		
		va_end(va);
	}
	
	zebu_parse_EOF(state);
	
	free_zebu_state(state);
	
	puts("accepts!");
}

int main()
{
	check("ABCCBA", NULL);
	
	check("ABC", "CBA", NULL);
	
	check("abc", NULL);
	
	check("abc::x!", NULL);
	
	check("a", "b", "c", ":", ":", "x", "!", NULL);
	
	check("bbaa", NULL);
	
	check("BaaB", "aBBa", NULL);
	
	check("abcc:x.", NULL);
	
	check("ABBABCCBCAAC", NULL);
	
	return 0;
}
















