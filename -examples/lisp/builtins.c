
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "argv0.h"
#include "value.h"
#include "scope.h"
#include "evaluate.h"
#include "builtins.h"

struct value* and_builtin(struct scope* scope, struct value** parameters, unsigned n)
{
	bool value = true;
	
	for (unsigned i = 0; value && i < n; i++)
	{
		struct value* ele = parameters[i];
		
		if (ele->kind != vk_boolean)
		{
			fprintf(stderr, "%s: builtin and function only supports boolean types!\n", argv0);
			exit(1);
		}
		
		value = ele->boolean;
	}
	
	return new_boolean_value(value);
}

struct value* or_builtin(struct scope* scope, struct value** parameters, unsigned n)
{
	bool value = false;
	
	for (unsigned i = 0; !value && i < n; i++)
	{
		struct value* ele = parameters[i];
		
		if (ele->kind != vk_boolean)
		{
			fprintf(stderr, "%s: builtin or function only supports boolean types!\n", argv0);
			exit(1);
		}
		
		value = ele->boolean;
	}
	
	return new_boolean_value(value);
}

struct value* bool_builtin(struct scope* scope, struct value** parameters, unsigned argc)
{
	
	if (argc != 1)
	{
		fprintf(stderr, "usage: (bool <value>)\n");
		exit(1);
	}
	
	struct value *first = parameters[0];
	
	switch (first->kind)
	{
		case vk_integer:
			return new_boolean_value(!!first->integer);
			
		default:
			assert(!"TODO");
			break;
	}
}

struct value* sum_builtin(struct scope* scope, struct value** parameters, unsigned n)
{
	signed long sum = 0;
	
	for (unsigned i = 0; i < n; i++)
	{
		struct value* ele = parameters[i];
		
		if (ele->kind != vk_integer)
		{
			fprintf(stderr, "%s: builtin sum function only supports adding"
				" integer types!\n", argv0);
			exit(1);
		}
		
		sum += ele->integer;
	}
	
	return new_integer_value(sum);
}

struct value* subtract_builtin(struct scope* scope, struct value** parameters, unsigned n)
{
	signed long sum = 0;
	
	for (unsigned i = 0; i < n; i++)
	{
		struct value* ele = parameters[i];
		
		if (ele->kind != vk_integer)
		{
			fprintf(stderr, "%s: builtin subtract function only supports adding"
				" integer types!\n", argv0);
			exit(1);
		}
		
		if (i)
			sum -= ele->integer;
		else
			sum = ele->integer;
	}
	
	return new_integer_value(sum);
}

struct value* product_builtin(struct scope* scope, struct value** parameters, unsigned n)
{
	signed long product = 1;
	
	for (unsigned i = 0; i < n; i++)
	{
		struct value* ele = parameters[i];
		
		if (ele->kind != vk_integer)
		{
			fprintf(stderr, "%s: builtin product function only supports adding"
				" integer types!\n", argv0);
			exit(1);
		}
		
		product *= ele->integer;
	}
	
	return new_integer_value(product);
}

struct value* mod_builtin(struct scope* scope, struct value** parameters, unsigned argc)
{
	struct value *first, *second;
	
	if (false
		|| argc != 2
		|| ( first = parameters[0])->kind != vk_integer
		|| (second = parameters[1])->kind != vk_integer)
	{
		fprintf(stderr, "usage: (mod <integer> <integer>)\n");
		exit(1);
	}
	
	return new_integer_value(first->integer % second->integer);
}


struct value* divide_builtin(struct scope* scope, struct value** parameters, unsigned n)
{
	signed long quotient = 0;
	
	for (unsigned i = 0; i < n; i++)
	{
		struct value* ele = parameters[i];
		
		if (ele->kind != vk_integer)
		{
			fprintf(stderr, "%s: builtin divide function only supports adding"
				" integer types!\n", argv0);
			exit(1);
		}
		
		if (i)
			quotient /= ele->integer;
		else
			quotient = ele->integer;
	}
	
	return new_integer_value(quotient);
}

struct value* less_builtin(struct scope* scope, struct value** parameters, unsigned argc)
{
	struct value* first, *second;
	
	if (false
		|| argc != 2
		|| (first  = parameters[0])->kind != vk_integer
		|| (second = parameters[1])->kind != vk_integer)
	{
		fprintf(stderr, "%s: builtin '<' function only supports integer "
			"types!\n", argv0);
		exit(1);
	}
	
	return new_boolean_value(first->integer < second->integer);
}

struct value* greater_builtin(struct scope* scope, struct value** parameters, unsigned argc)
{
	struct value* first, *second;
	
	if (false
		|| argc != 2
		|| (first  = parameters[0])->kind != vk_integer
		|| (second = parameters[1])->kind != vk_integer)
	{
		fprintf(stderr, "%s: builtin '>' function only supports integer "
			"types!\n", argv0);
		exit(1);
	}
	
	return new_boolean_value(first->integer > second->integer);
}

struct value* equals_builtin(struct scope* scope, struct value** parameters, unsigned argc)
{
	struct value* first, *second;
	
	if (false
		|| argc != 2
		|| (first  = parameters[0])->kind != vk_integer
		|| (second = parameters[1])->kind != vk_integer)
	{
		fprintf(stderr, "%s: builtin '=' function only supports integer "
			"types!\n", argv0);
		exit(1);
	}
	
	return new_boolean_value(first->integer == second->integer);
}

static signed long ipow(signed long base, signed long exp)
{
	int result = 1;
	for (;;)
	{
		if (exp & 1)
			result *= base;
		exp >>= 1;
		if (!exp)
			break;
		base *= base;
	}

	return result;
}

struct value* expo_builtin(struct scope* scope, struct value** parameters, unsigned n)
{
	signed long value = 0;
	
	for (unsigned i = 0; i < n; i++)
	{
		struct value* ele = parameters[i];
		
		if (ele->kind != vk_integer)
		{
			fprintf(stderr, "%s: builtin divide function only supports adding"
				" integer types!\n", argv0);
			exit(1);
		}
		
		if (!i)
			value = ele->integer;
		else if (ele->integer <= 0)
			value = 0;
		else
			value = ipow(value, ele->integer);
	}
	
	return new_integer_value(value);
}


struct value* strconcat_builtin(struct scope* scope, struct value** parameters, unsigned argc)
{
	char* chars = NULL;
	unsigned n = 0, cap = 0;
	
	for (unsigned i = 0; i < argc; i++)
	{
		struct value* ele = parameters[i];
		
		if (ele->kind != vk_string)
		{
			fprintf(stderr, "%s: builtin string concat function only supports lists!\n", argv0);
			exit(1);
		}
		
		while (n + ele->string.length >= cap)
		{
			cap = cap << 1 ?: 1;
			chars = realloc(chars, cap * sizeof(*chars));
		}
		
		memcpy(chars + n, ele->string.data, ele->string.length);
		
		n += ele->string.length;
	}
	
	struct value* retval = new_string_value(chars, n);
	free(chars);
	return retval;
}

struct value* concat_builtin(struct scope* scope, struct value** parameters, unsigned argc)
{
	struct value** list = NULL;
	unsigned n = 0, cap = 0;
	
	for (unsigned i = 0; i < argc; i++)
	{
		struct value* ele = parameters[i];
		
		if (ele->kind != vk_list)
		{
			fprintf(stderr, "%s: builtin concat function only supports lists!\n", argv0);
			exit(1);
		}
		
		while (n + ele->list.length >= cap)
		{
			cap = cap << 1 ?: 1;
			list = realloc(list, cap * sizeof(*list));
		}
		
		unsigned j, m;
		
		for (j = 0, m = ele->list.length; j < m; j++)
		{
			list[n + j] = inc_value(ele->list.data[j]);
		}
		
		n += m;
	}
	
	return new_list_value(list, n);
}


struct value* prepend_builtin(struct scope* scope, struct value** parameters, unsigned argc)
{
	struct value * first, *second;
	
	if (argc != 2 || (first = parameters[0], second = parameters[1])->kind != vk_list)
	{
		fprintf(stderr, "usage: (prepend <element> <list>)\n");
		exit(1);
	}
	
	unsigned n = second->list.length;
	
	struct value** list = malloc((n + 1) * sizeof(*list));
	
	list[0] = inc_value(first);
	
	for (unsigned i = 0; i < n; i++)
		list[i + 1] = inc_value(second->list.data[i]);
		
	return new_list_value(list, n + 1);
}


struct value* append_builtin(struct scope* scope, struct value** parameters, unsigned argc)
{
	struct value * first, *second;
	
	if (argc != 2 || (second = parameters[1], first = parameters[0])->kind != vk_list)
	{
		fprintf(stderr, "usage: (append <list>, <element>)\n");
		exit(1);
	}
	
	unsigned n = first->list.length;
	
	struct value** list = malloc((n + 1) * sizeof(*list));
	
	for (unsigned i = 0; i < n; i++)
		list[i] = inc_value(first->list.data[i]);
		
	list[n] = inc_value(second);
	
	return new_list_value(list, n + 1);
}


struct value* map_builtin(struct scope* scope, struct value** parameters, unsigned argc)
{
	if (argc < 2)
	{
		fprintf(stderr, "usage: (map <function> <list> ...)\n");
		exit(1);
	}
	
	struct value* function = parameters[0];
	
	if (function->kind != vk_builtin && function->kind != vk_lambda)
	{
		fprintf(stderr, "usage: (map <function> <list> ...)\n");
		exit(1);
	}
	
	unsigned i, j, n = -1;
	
	for (i = 1; i < argc; i++)
	{
		struct value* ele = parameters[i];
		
		if (ele->kind != vk_list)
		{
			fprintf(stderr, "usage: (map <function> <list> ...)\n");
			exit(1);
		}
		
		if (ele->list.length < n)
		{
			n = ele->list.length;
		}
	}
	
	struct value** list = malloc(n * sizeof(*list));
	
	struct value** subparameters = malloc((argc - 1) * sizeof(*subparameters));
	
	for (i = 0; i < n; i++)
	{
		for (j = 1; j < argc; j++)
		{
			subparameters[j - 1] = parameters[j]->list.data[i];
		}
		
		list[i] = evaluate_function(scope, function, subparameters, argc - 1);
	}
	
	free(subparameters);
	
	return new_list_value(list, n);
}


struct value* list_builtin(struct scope* scope, struct value** parameters, unsigned argc)
{
	struct value** list = malloc(argc * sizeof(*list));
	
	for (unsigned i = 0; i < argc; i++)
	{
		list[i] = inc_value(parameters[i]);
	}
	
	return new_list_value(list, argc);
}

struct value* range_builtin(struct scope* scope, struct value** parameters, unsigned argc)
{
	signed long start = 0, stop, step = 1;
	
	switch (argc)
	{
		case 1:
		{
			struct value* first = parameters[0];
			if (first->kind != vk_integer)
			{
				assert(!"TODO");
			}
			stop = first->integer;
			break;
		}
		
		case 2:
		{
			struct value* first = parameters[0];
			if (first->kind != vk_integer)
			{
				assert(!"TODO");
			}
			start = first->integer;
			struct value* second = parameters[1];
			if (second->kind != vk_integer)
			{
				assert(!"TODO");
			}
			stop = second->integer;
			break;
		}
		
		default:
			assert(!"TODO");
			break;
	}
	
	unsigned n = (stop - start) / step;
	
	struct value** list = malloc(n * sizeof(*list));
	
	for (unsigned i = 0; i < n; i++)
	{
		list[i] = new_integer_value(i + start);
	}
	
	return new_list_value(list, n);
}

struct value* filter_builtin(struct scope* scope, struct value** parameters, unsigned argc)
{
	struct value* first, *second;
	
	if (false
		|| argc != 2
		|| ((first = parameters[0])->kind != vk_lambda && first->kind != vk_builtin)
		|| (second = parameters[1])->kind != vk_list)
	{
		fprintf(stderr, "usage: (filter <function> <list>)\n");
		exit(1);
	}
	
	struct {
		struct value** data;
		unsigned n, cap;
	} list = {};
	
	for (unsigned i = 0, n = second->list.length; i < n; i++)
	{
		struct value* element = second->list.data[i];
		
		struct value* result = evaluate_function(scope, first, &element, 1);
		
		if (result->kind != vk_boolean)
		{
			fprintf(stderr, "filter: function must result in a boolean!\n");
			exit(1);
		}
		
		if (result->boolean)
		{
			if (list.n == list.cap)
			{
				list.cap = list.cap << 1 ?: 1;
				list.data = realloc(list.data, list.cap * sizeof(*list.data));
			}
			
			list.data[list.n++] = inc_value(element);
		}
		
		free_value(result);
	}
	
	return new_list_value(list.data, list.n);
}

struct value* reduce_builtin(struct scope* scope, struct value** parameters, unsigned argc)
{
	struct value* first, *second;
	
	if (false
		|| argc != 3
		|| ((first = parameters[0])->kind != vk_lambda && first->kind != vk_builtin)
		|| (second = parameters[1])->kind != vk_list)
	{
		fprintf(stderr, "usage: (reduce <function> <list> <initial>)\n");
		exit(1);
	}
	
	struct value* result = inc_value(parameters[2]);
	
	for (unsigned i = 0, n = second->list.length; i < n; i++)
	{
		struct value* element = second->list.data[i];
		
		struct value* new = evaluate_function(scope, first, (struct value*[]){result, element}, 2);
		
		free_value(result), result = new;
	}
	
	return result;
}

struct value* first_builtin(struct scope* scope, struct value** parameters, unsigned argc)
{
	struct value* first;
	
	if (false
		|| argc != 1
		|| (first = parameters[0])->kind != vk_list)
	{
		fprintf(stderr, "usage: (first <list>)\n");
		exit(1);
	}
	
	if (!first->list.length)
	{
		fprintf(stderr, "first: list cannot be empty!\n");
		exit(1);
	}
	
	return inc_value(first->list.data[0]);
}

struct value* len_builtin(struct scope* scope, struct value** parameters, unsigned argc)
{
	struct value* first;
	
	if (false
		|| argc != 1
		|| (first = parameters[0])->kind != vk_list)
	{
		fprintf(stderr, "usage: (list <list>)\n");
		exit(1);
	}
	
	return new_integer_value(first->list.length);
}



struct value* lambda_builtin(struct scope* scope, struct value** parameters, unsigned argc)
{
	if (argc != 2)
	{
		fprintf(stderr, "usage: (lambda `(variables) `(expression))\n");
		exit(1);
	}
	
	struct value* arguments = parameters[0];
	struct value* expression = parameters[1];
	
	return new_lambda_value(arguments, expression);
}

struct value* define_builtin(struct scope* scope, struct value** parameters, unsigned argc)
{
	if (argc != 3)
	{
		fprintf(stderr, "usage: (define <variable> <value> <expression>)\n");
		exit(1);
	}
	
	struct value* variable = parameters[0];
	struct value* value = parameters[1];
	struct value* expression = parameters[2];
	
	if (variable->kind != vk_identifier)
	{
		fprintf(stderr, "usage: (define <variable> <value> <expression>)\n");
		exit(1);
	}
	
	scope_push(scope);
	
	scope_define(scope, variable->identifier, value);
	
	struct value* result = evaluate(scope, expression);
	
	scope_pop(scope);
	
	return result;
}

struct value* if_builtin(struct scope* scope, struct value** parameters, unsigned argc)
{
	if (argc != 3)
	{
		fprintf(stderr, "usage: (if <conditional> <true-value> <false-value>)\n");
		exit(1);
	}
	
	struct value* conditional = parameters[0];
	struct value* true_case = parameters[1];
	struct value* false_case = parameters[2];
	
	if (conditional->kind != vk_boolean)
	{
		fprintf(stderr, "usage: (if <conditional> <true-value> <false-value>)\n");
		exit(1);
	}
	
	if (conditional->boolean)
		return evaluate(scope, true_case);
	else
		return evaluate(scope, false_case);
}






















































