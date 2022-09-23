
#include <stdio.h>

#include "parser.h"
#include "evaluate.h"

int main()
{
	struct zebu_$start* root;
	
	while ((root = zebu_parse()))
	{
		if (root->exit)
			break;
		
		double result = evaluate(root);
		
		printf("%g\n", result);
		
		free_zebu_$start(root);
	}
	
	return 0;
}

