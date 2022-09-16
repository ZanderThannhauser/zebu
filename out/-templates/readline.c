
#include <readline/readline.h>
#include <readline/history.h>

#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

{{LEXER_TABLE}}

{{LEXER_STARTS_TABLE}}

{{LEXER_ACCEPTS_TABLE}}

{{LEXER_EOF_TABLE}}

{{SHIFT_TABLE}}

{{REDUCE_TABLE}}

{{GOTO_TABLE}}

{{PARSE_TREE_INC_FUNCTIONS}}

{{PARSE_TREE_FREE_FUNCTIONS}}

#define N(array) (sizeof(array) / sizeof(*array))

struct $start* {{PREFIX}}_parse()
{
	struct { unsigned* data, n, cap; } yacc = {};
	
	struct { void** data; unsigned n, cap; } data = {};
	
	void push_state(unsigned state)
	{
		if (yacc.n + 1 >= yacc.cap)
		{
			yacc.cap = yacc.cap << 1 ?: 1;
			yacc.data = realloc(yacc.data, sizeof(*yacc.data) * yacc.cap);
		}
		
		yacc.data[yacc.n++] = state;
	}
	
	void push_data(void* element)
	{
		if (data.n + 1 >= data.cap)
		{
			data.cap = data.cap << 1 ?: 1;
			data.data = realloc(data.data, sizeof(*data.data) * data.cap);
		}
		
		data.data[data.n++] = element;
	}
	
	char* line = readline(">>> ");
	
	if (!line) return NULL;
	
	char* lexer = line;
	
	unsigned y, s, r, t;
	
	void* td;
	
	void read_token(unsigned l)
	{
		char* begin = lexer, *f = NULL;
		
		unsigned original_l = l, a, b, c;
		
		while (1)
		{
			if ((c = *lexer))
			{
				a = l < N({{PREFIX}}_lexer) && c < N(*{{PREFIX}}_lexer) ? {{PREFIX}}_lexer[l][c] : 0;
			}
			else
			{
				a = l < N({{PREFIX}}_lexer_EOFs) ? {{PREFIX}}_lexer_EOFs[l] : 0;
				
				if (!a)
				{
					// it would be cool if it would read another line
					// if there wasn't an EOF transition
				}
			}
			
			b = l < N({{PREFIX}}_lexer_accepts) ? {{PREFIX}}_lexer_accepts[l] : 0;
			
			if (a)
			{
				if (b)
				{
					l = a, t = b, f = lexer++;
				}
				else
				{
					l = a;
					if (c) lexer++;
				}
			}
			else if (b)
			{
				if (b == 1)
				{
					l = original_l, begin = lexer, f = NULL;
				}
				else
				{
					struct token* token = malloc(sizeof(*token));
					token->refcount = 1;
					token->data = memcpy(malloc(lexer - begin), begin, lexer - begin);
					token->len = lexer - begin;
					t = b, td = token;
					break;
				}
			}
			else if (t)
			{
				assert(!"172" || f);
				#if 0
				process_token(t);
				l = {{PREFIX}}_starts[yacc.data[yacc.n - 1]], i = f, t = 0;
				#endif
			}
			else
			{
				assert(!"TODO");
			}
		}
	}
	
	y = 1, push_state(y);
	
	read_token({{PREFIX}}_lexer_starts[y]);
	
	void* root;
	
	while (yacc.n)
	{
		if (y < N({{PREFIX}}_shifts) && t < N(*{{PREFIX}}_shifts) && (s = {{PREFIX}}_shifts[y][t]))
		{
			y = s, push_state(y), push_data(td);
			read_token({{PREFIX}}_lexer_starts[y]);
		}
		else if (y < N({{PREFIX}}_reduces) && t < N(*{{PREFIX}}_reduces) && (r = {{PREFIX}}_reduces[y][t]))
		{
			unsigned g;
			
			void* d;
			
			{{REDUCTIONRULE_SWITCH}}
			
			if (g == {{START_GRAMMAR_ID}})
			{
				free_token(td);
				yacc.n = 0, root = d;
			}
			else
			{
				y = yacc.data[yacc.n - 1];
				
				assert(y < N({{PREFIX}}_gotos) && g < N(*{{PREFIX}}_gotos));
				
				s = {{PREFIX}}_gotos[y][g];
				
				y = s, push_state(y), push_data(d);
			}
		}
		else
		{
			assert(!"190");
		}
	}
	
	assert(!data.n);
	
	add_history(line);
	
	free(line);
	
	free(yacc.data);
	free(data.data);
	
	return root;
}










