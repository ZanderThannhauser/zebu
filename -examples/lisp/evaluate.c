
#include <stdlib.h>
#include <assert.h>

#include "scope.h"
#include "value.h"
#include "evaluate.h"

struct value* evaluate_function(
	struct scope* scope,
	struct value* function,
	struct value** parameters,
	unsigned argc)
{
	struct value* retval;
	
	switch (function->kind)
	{
		case vk_builtin:
		{
			retval = function->builtin(scope, parameters, argc);
			break;
		}
		
		case vk_lambda:
		{
			scope_push(scope);
			
			struct value* const arguments = function->lambda.arguments;
			
			if (arguments->list.length != argc)
			{
				assert(!"TODO");
			}
			
			for (unsigned i = 0, n = arguments->list.length; i < n; i++)
			{
				struct value* ele = arguments->list.data[i];
				
				if (ele->kind != vk_identifier)
				{
					assert(!"TODO");
				}
				
				scope_define(scope, ele->identifier, parameters[i]);
			}
			
			retval = evaluate(scope, function->lambda.expression);
			
			scope_pop(scope);
			break;
		}
		
		default:
			assert(!"TODO");
			break;
	}
	
	return retval;
}

struct value* evaluate(struct scope* scope, struct value* value)
{
	struct value* retval;
	
	switch (value->kind)
	{
		case vk_boolean:
		case vk_integer:
		case vk_string:
		{
			retval = inc_value(value);
			break;
		}
		
		case vk_backtick:
		{
			retval = inc_value(value->backtick);
			break;
		}
		
		case vk_identifier:
		{
			return scope_lookup(scope, value->identifier);
		}
		
		case vk_list:
		{
			if (value->list.length)
			{
				struct value* first = value->list.data[0];
				struct value* after = evaluate(scope, first);
				
				unsigned n = value->list.length - 1;
				struct value** parameters = malloc(n * sizeof(*parameters));
				
				for (unsigned i = 0; i < n; i++)
				{
					parameters[i] = evaluate(scope, value->list.data[i + 1]);
				}
				
				retval = evaluate_function(scope, after, parameters, n);
				
				for (unsigned i = 0; i < n; i++)
				{
					free_value(parameters[i]);
				}
				
				free(parameters);
				
				free_value(after);
				break;
			}
			else
			{
				retval = inc_value(value);
			}
		}
		
		case vk_lambda:
			assert(!"evaluate");
			break;
		
		case vk_builtin:
			assert(!"evaluate");
			break;
		
		default:
			assert(!"evaluate");
			break;
	}
	
	return retval;
}


