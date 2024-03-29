
#include <math.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "parser.h"
#include "evaluate.h"

static double evaluate_add(struct zebu_add* add);

static double evaluate_highest(struct zebu_highest* highest)
{
	double retval;
	
	if (highest->subexpression)
	{
		retval = evaluate_add(highest->subexpression->add);
	}
	else if (highest->pi)
	{
		retval = M_PI;
	}
	else if (highest->function)
	{
		unsigned char* funcname = highest->function->data;
		unsigned funclen = highest->function->len;
		
		while (*funcname == ' ')
			funcname++, funclen--;
		
		if (funclen == 3 && !memcmp(funcname, "sin", 3))
		{
			retval = sin(evaluate_add(highest->arg->add));
		}
		else if (funclen == 3 && !memcmp(funcname, "cos", 3))
		{
			retval = cos(evaluate_add(highest->arg->add));
		}
		else if (funclen == 3 && !memcmp(funcname, "tan", 3))
		{
			retval = tan(evaluate_add(highest->arg->add));
		}
		else if (funclen == 4 && !memcmp(funcname, "sqrt", 4))
		{
			retval = sqrt(evaluate_add(highest->arg->add));
		}
		else
		{
			fprintf(stderr, "unknown function '%.*s'!\n", funclen, funcname);
			exit(1);
		}
	}
	else
	{
		retval = highest->number;
	}
	
	return retval;
}

static double evaluate_expo(struct zebu_expo* expo)
{
	double subresult = evaluate_highest(expo->base);
	
	for (unsigned i = 0, n = expo->expomes.n; i < n; i++)
	{
		subresult = pow(subresult, evaluate_highest(expo->expomes.data[i]));
	}
	
	return subresult;
}

static double evaluate_multiply(struct zebu_multiply* multiply)
{
	double subresult = evaluate_expo(multiply->base);
	
	for (unsigned i = 0, n = multiply->multiplymes.n; i < n; i++)
	{
		subresult *= evaluate_expo(multiply->multiplymes.data[i]);
	}
	
	for (unsigned i = 0, n = multiply->dividemes.n; i < n; i++)
	{
		subresult /= evaluate_expo(multiply->dividemes.data[i]);
	}
	
	return subresult;
}

static double evaluate_add(struct zebu_add* add)
{
	double subresult = evaluate_multiply(add->base);
	
	for (unsigned i = 0, n = add->addmes.n; i < n; i++)
	{
		subresult += evaluate_multiply(add->addmes.data[i]);
	}
	
	for (unsigned i = 0, n = add->submes.n; i < n; i++)
	{
		subresult -= evaluate_multiply(add->submes.data[i]);
	}
	
	return subresult;
}

double evaluate(struct zebu_$start* start)
{
	return evaluate_add(start->root->add);
}











