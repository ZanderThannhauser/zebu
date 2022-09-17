
#include <stdbool.h>

struct zebu_value;
struct scope;

struct value
{
	enum {
		vk_boolean,
		vk_integer,
		vk_string,
		vk_identifier,
		vk_backtick,
		vk_list,
		vk_lambda,
		vk_builtin,
	} kind;
	
	union {
		bool boolean;
		signed long integer;
		struct {
			char* data;
			unsigned length;
		} string;
		char* identifier;
		struct value* backtick;
		struct {
			struct value** data;
			unsigned length;
		} list;
		struct {
			struct value *arguments, *expression;
		} lambda;
		struct value* (*builtin)(
			struct scope* scope,
			struct value** parameters,
			unsigned argc);
	};
	
	unsigned refcount;
};

struct value* new_value_from_ptree(struct zebu_value* value);

struct value* new_boolean_value(bool boolean);

struct value* new_identifier_value(const char* identifier, unsigned len);

struct value* new_integer_value(signed long integer);

struct value* new_string_value(const char* str, unsigned len);

struct value* new_backtick_value(struct value* backtick);

struct value* new_lambda_value(struct value* arguments, struct value* expression);

struct value* new_builtin_value(struct value* (*)(struct scope* scope, struct value** parameters, unsigned n));

struct value* new_list_value(struct value** list, unsigned n);

struct value* inc_value(struct value* value);

void free_value(struct value* value);























