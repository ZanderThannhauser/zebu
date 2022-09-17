
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "argv0.h"
#include "parser.h"
#include "value.h"

struct value* new_value_from_ptree(struct zebu_value* ptree)
{
	if (ptree->boolean)
	{
		if (ptree->boolean->data[1] == 't')
			return new_boolean_value(true);
		else
			return new_boolean_value(false);
	}
	else if (ptree->number)
	{
		char* temp = strndup((void*) ptree->number->data, ptree->number->len);
		char* m;
		errno = 0;
		
		signed long value = strtol(temp, &m, 0);
		
		if (errno || *m)
		{
			fprintf(stderr, "%s: strtol(\"%s\"): %m\n", argv0, temp);
			exit(1);
		}
		
		free(temp);
		return new_integer_value(value);
	}
	else if (ptree->string)
	{
		return new_string_value((void*) (ptree->string->data + 1), ptree->string->len - 2);
	}
	else if (ptree->identifier)
	{
		return new_identifier_value((void*) ptree->identifier->data, ptree->identifier->len);
	}
	else if (ptree->list.n)
	{
		unsigned n = ptree->list.n;
		struct value** list = malloc(n * sizeof(*list));
		
		for (unsigned i = 0; i < n; i++)
		{
			list[i] = new_value_from_ptree(ptree->list.data[i]);
		}
		
		return new_list_value(list, n);
	}
	else if (ptree->backtick)
	{
		return new_backtick_value(new_value_from_ptree(ptree->backtick));
	}
	else
	{
		assert(!"TODO");
	}
}

struct value* new_boolean_value(bool boolean)
{
	struct value* this = malloc(sizeof(*this));
	this->kind = vk_boolean;
	this->boolean = boolean;
	this->refcount = 1;
	return this;
}
struct value* new_integer_value(signed long integer)
{
	struct value* this = malloc(sizeof(*this));
	this->kind = vk_integer;
	this->integer = integer;
	this->refcount = 1;
	return this;
}

struct value* new_string_value(const char* str, unsigned len)
{
	struct value* this = malloc(sizeof(*this));
	this->kind = vk_string;
	this->string.data = memcpy(malloc(len), str, len);
	this->string.length = len;
	this->refcount = 1;
	return this;
}

struct value* new_identifier_value(const char* identifier, unsigned len)
{
	struct value* this = malloc(sizeof(*this));
	this->kind = vk_identifier;
	this->identifier = strndup(identifier, len);
	this->refcount = 1;
	return this;
}

struct value* new_backtick_value(struct value* backtick)
{
	struct value* this = malloc(sizeof(*this));
	this->kind = vk_backtick;
	this->backtick = backtick;
	this->refcount = 1;
	return this;
}

struct value* new_list_value(struct value** list, unsigned n)
{
	struct value* this = malloc(sizeof(*this));
	this->kind = vk_list;
	this->list.data = list;
	this->list.length = n;
	this->refcount = 1;
	return this;
}

struct value* new_lambda_value(struct value* arguments, struct value* expression)
{
	struct value* this = malloc(sizeof(*this));
	this->kind = vk_lambda;
	this->lambda.arguments = inc_value(arguments);
	this->lambda.expression = inc_value(expression);
	this->refcount = 1;
	return this;
}

struct value* new_builtin_value(struct value* (*builtin)(struct scope* scope, struct value**, unsigned))
{
	struct value* this = malloc(sizeof(*this));
	this->kind = vk_builtin;
	this->builtin = builtin;
	this->refcount = 1;
	return this;
}

struct value* inc_value(struct value* value)
{
	if (value) value->refcount++;
	return value;
}

void free_value(struct value* value)
{
	if (value && !--value->refcount)
	{
		switch (value->kind)
		{
			case vk_boolean:
			case vk_integer:
			case vk_builtin:
				break;
			
			case vk_string:
				free(value->string.data);
				break;
			
			case vk_identifier:
				free(value->identifier);
				break;
			
			case vk_backtick:
				free_value(value->backtick);
				break;
			
			case vk_list:
			{
				for (unsigned i = 0, n = value->list.length; i < n; i++)
				{
					free_value(value->list.data[i]);
				}
				
				free(value->list.data);
				break;
			}
			
			case vk_lambda:
			{
				free_value(value->lambda.arguments);
				free_value(value->lambda.expression);
				break;
			}
			
			default:
				assert(!"TODO");
				break;
		}
		
		free(value);
	}
}















