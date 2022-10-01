
#include <stdio.h>

#include "classic.h"

int main()
{
	puts("hello, world!");
	
	struct zebu_$start* root = zebu_parse((void*) "aabbcc::x!", 10);
	
	free_zebu_$start(root);
	
	return 0;
}

