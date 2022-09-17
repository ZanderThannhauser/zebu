
#include <stdio.h>
#include <assert.h>

#include "value.h"
#include "print.h"

static void helper(struct value* value)
{
	switch (value->kind)
	{
		case vk_boolean:
			fputs(value->boolean ? "#t" : "#f", stdout);
			break;
		
		case vk_integer:
		{
			printf("%li", value->integer);
			break;
		}
		
		case vk_string:
		{
			printf("\"%.*s\"", (int) value->string.length, value->string.data);
			break;
		}
		
		case vk_identifier:
			fputs(value->identifier, stdout);
			break;
		
		case vk_list:
		{
			putchar('(');
			
			for (unsigned i = 0, n = value->list.length; i < n; i++)
			{
				helper(value->list.data[i]);
				
				if (i + 1 < n)
					putchar(' ');
			}
			
			putchar(')');
			break;
		}
		
		case vk_backtick:
			assert(!"TODO");
			break;
		
		default:
			assert(!"TODO");
			break;
	}
}

void print(struct value* value)
{
	helper(value);
	puts("");
}












