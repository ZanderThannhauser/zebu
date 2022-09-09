
#include <stdio.h>

#include "parser.h"
#include "evaluate.h"

int main()
{
	struct $start* root;
	
	while ((root = zebu_parse()))
	{
		if (root->exit)
			break;
		
		double result = evaluate(root);
		
		printf("%g\n", result);
		
		free_$start_ptree(root);
	}
	
	return 0;
}

