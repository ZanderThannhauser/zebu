
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

{{SHIFT_TABLE}}

{{REDUCE_TABLE}}

{{GOTO_TABLE}}

{{LEXER_TRANSITION_TABLE}}

{{LEXER_STARTS_TABLE}}

{{LEXER_ACCEPTS_TABLE}}

{{LEXER_EOF_TABLE}}

#ifdef ZEBU_DEBUG
{{PARSE_TREE_PRINT_TREE_FUNCTIONS}}
#endif

{{PARSE_TREE_INC_FUNCTIONS}}

{{PARSE_TREE_FREE_FUNCTIONS}}

#define N(array) (sizeof(array) / sizeof(*array))

#ifdef ZEBU_DEBUG
static void escape(char *out, unsigned char in)
{
	switch (in)
	{
		case ' ':
		case '~':
		case '!':
		case '@':
		case '#':
		case '$':
		case '%':
		case '^':
		case '&':
		case '*':
		case '-':
		case '+':
		case '=':
		case '|':
		case '<': case '>':
		case '(': case ')':
		case '{': case '}':
		case '[': case ']':
		case ':': case ';':
		case ',': case '.':
		case '_':
		case '0' ... '9':
		case 'a' ... 'z':
		case 'A' ... 'Z':
			*out++ = in;
			*out = 0;
			break;
		
		case '\\': *out++ = '\\', *out++ = '\\', *out = 0; break;
		
		case '\"': *out++ = '\\', *out++ = '\"', *out = 0; break;
		
		case '\t': *out++ = '\\', *out++ = 't', *out = 0; break;
		
		case '\n': *out++ = '\\', *out++ = 'n', *out = 0; break;
		
		default:
			sprintf(out, "\\x%02X", in);
			break;
	}
}
#endif

struct {{PREFIX}}_state
{
	struct { unsigned* data, n, cap; } y;
	struct { void** data; unsigned n, cap; } d;
	struct { unsigned char* data, n, cap; } l;
	unsigned lstate, t, f, i, backup_lstate;
};

#ifdef ZEBU_DEBUG
static void ddprintf(struct {{PREFIX}}_state* this, const char* fmt, ...)
{
	for (unsigned i = 0, n = this->y.n; i < n; i++)
		printf("%u ", this->y.data[i]);
	
	printf("| ");
	
	va_list va;
	va_start(va, fmt);
	vprintf(fmt, va);
	va_end(va);
}
#endif

static void push_state(struct {{PREFIX}}_state* this, unsigned ystate)
{
	if (this->y.n == this->y.cap)
	{
		this->y.cap = this->y.cap << 1 ?: 1;
		this->y.data = realloc(this->y.data, sizeof(*this->y.data) * this->y.cap);
		
		assert(this->y.data);
	}
	
	this->y.data[this->y.n++] = ystate;
}

static void push_data(struct {{PREFIX}}_state* this, void* data)
{
	if (this->d.n == this->d.cap)
	{
		this->d.cap = this->d.cap << 1 ?: 1;
		this->d.data = realloc(this->d.data, sizeof(*this->d.data) * this->d.cap);
		
		assert(this->d.data);
	}
	
	this->d.data[this->d.n++] = data;
}

static void append(struct {{PREFIX}}_state* this, unsigned char c)
{
	while (this->l.n == this->l.cap)
	{
		this->l.cap = this->l.cap << 1 ?: 1;
		this->l.data = realloc(this->l.data, this->l.cap);
	}
	
	this->l.data[this->l.n++] = c;
}

struct {{PREFIX}}_state* new_{{PREFIX}}_state()
{
	struct {{PREFIX}}_state* this = malloc(sizeof(*this));
	
	assert(this);
	
	this->y.data = NULL, this->y.n = 0, this->y.cap = 0;
	this->d.data = NULL, this->d.n = 0, this->d.cap = 0;
	this->l.data = NULL, this->l.n = 0, this->l.cap = 0;
	
	this->lstate = 1;
	this->backup_lstate = 1;
	this->i = 0;
	this->t = 0;
	this->f = 0;
	
	push_state(this, 1);
	
	return this;
}

void {{PREFIX}}_reset(struct {{PREFIX}}_state* this)
{
	this->y.n = 0, this->y.cap = 0;
	this->d.n = 0, this->d.cap = 0;
	this->l.n = 0, this->l.cap = 0;
	
	this->lstate = 1;
	this->backup_lstate = 1;
	this->i = 0;
	this->t = 0;
	this->f = 0;
	
	push_state(this, 1);
}

#define N(array) (sizeof(array) / sizeof(*array))

static void process_token(struct {{PREFIX}}_state* this, unsigned t, void* td)
{
	unsigned s, r, y = this->y.data[this->y.n - 1];
	
	while (y < N({{PREFIX}}_reduces) && t < N(*{{PREFIX}}_reduces) && (r = {{PREFIX}}_reduces[y][t]))
	{
		#ifdef ZEBU_DEBUG
		ddprintf(this, "r == %u\n", r);
		#endif
		
		unsigned g;
		void* d;
		
		typeof(this->y) yacc = this->y;
		typeof(this->d) data = this->d;
		
		{{REDUCTION_RULE_SWITCH}}
		
		this->y = yacc;
		this->d = data;
		
		if (g == {{START_GRAMMAR_ID}})
		{
			free_{{PREFIX}}_token(td);
			this->y.n = 0, this->d.n = 0;
			push_data(this, d);
			return;
		}
		else
		{
			y = this->y.data[this->y.n - 1];
			
			#ifdef ZEBU_DEBUG
			ddprintf(this, "y = %u\n", y);
			#endif
			
			assert(y < N({{PREFIX}}_gotos) && g < N(*{{PREFIX}}_gotos));
			
			s = {{PREFIX}}_gotos[y][g];
			
			#ifdef ZEBU_DEBUG
			ddprintf(this, "s = %u\n", s);
			#endif
			
			y = s, push_state(this, y), push_data(this, d);
		}
	}
	
	s = y < N({{PREFIX}}_shifts) && t < N(*{{PREFIX}}_shifts) ? {{PREFIX}}_shifts[y][t] : 0;
	
	if (s)
	{
		y = s, push_state(this, y), push_data(this, td);
	}
	else
	{
		assert(!"TODO");
	}
}

void {{PREFIX}}_parse(struct {{PREFIX}}_state* this,
	const unsigned char* buffer,
	unsigned len)
{
	unsigned l = this->lstate, i = this->i, f = this->f, t = this->t;
	
	unsigned bl = this->backup_lstate;
	
	const unsigned char* end = buffer + len;
	
	#ifdef ZEBU_DEBUG
	char escaped[10];
	#endif
	
	unsigned char a, b, c;
	
	while (buffer < end)
	{
		if (i < this->l.n)
		{
			c = this->l.data[i];
		}
		else
		{
			c = *buffer++;
			append(this, c);
		}
		
		#ifdef ZEBU_DEBUG
		escape(escaped, c);
		ddprintf(this, "lexer: c = '%s' (0x%X)\n", escaped, c);
		#endif
		
		a = l < N({{PREFIX}}_lexer) && c < N(*{{PREFIX}}_lexer) ? {{PREFIX}}_lexer[l][c] : 0;
		b = l < N({{PREFIX}}_lexer_accepts) ? {{PREFIX}}_lexer_accepts[l] : 0;
		
		#ifdef ZEBU_DEBUG
		ddprintf(this, "lexer: \"%.*s\" (%u): a = %u, b = %u\n", this->l.n, this->l.data, i, a, b);
		#endif
		
		if (a)
		{
			if (b)
			{
				l = a, t = b, f = i++;
			}
			else
			{
				l = a, i++;
			}
		}
		else if (b)
		{
			if (b == 1)
			{
				#ifdef ZEBU_DEBUG
				ddprintf(this, "lexer: whitespace: \"%.*s\"\n", i, this->l.data);
				#endif
				
				memmove(this->l.data, this->l.data + i, this->l.n - i), this->l.n -= i;
				
				l = bl, t = 0, i = 0;
			}
			else
			{
				#ifdef ZEBU_DEBUG
				ddprintf(this, "lexer: token: \"%.*s\"\n", i, this->l.data);
				#endif
				
				struct {{PREFIX}}_token* token = malloc(sizeof(*token));
				token->refcount = 1;
				token->data = memcpy(malloc(i + 1), this->l.data, i);
				token->len = i;
				token->data[i] = 0;
				
				process_token(this, b, token);
				
				memmove(this->l.data, this->l.data + i, this->l.n - i), this->l.n -= i;
				
				bl = l = {{PREFIX}}_lexer_starts[this->y.data[this->y.n - 1]], f = 0, t = 0, i = 0;
			}
		}
		else if (t)
		{
			assert(!"256");
			#if 0
			process_token(this, t);
			l = {{PREFIX}}_starts[this->y.data[this->y.n - 1]], i = f, t = 0;
			#endif
		}
		else
		{
			assert(!"TODO");
		}
	}
	
	this->backup_lstate = bl;
	
	this->lstate = l, this->i = i, this->f = f, this->t = t;
}

struct zebu_$start* {{PREFIX}}_close(struct {{PREFIX}}_state* this)
{
	unsigned l = this->lstate, i = this->i, f = this->f, t = this->t;
	
	unsigned bl = this->backup_lstate;
	
	#ifdef ZEBU_DEBUG
	char escaped[10];
	#endif
	
	unsigned char a, b, c;
	
	while (1)
	{
		if (i < this->l.n)
		{
			c = this->l.data[i];
			
			#ifdef ZEBU_DEBUG
			escape(escaped, c);
			ddprintf(this, "lexer: c = '%s' (0x%X)\n", escaped, c);
			#endif
			
			a = l < N({{PREFIX}}_lexer) && c < N(*{{PREFIX}}_lexer) ? {{PREFIX}}_lexer[l][c] : 0;
		}
		else
		{
			c = EOF;
			
			#ifdef ZEBU_DEBUG
			ddprintf(this, "lexer: c = <EOF>\n");
			#endif
			
			a = l < N({{PREFIX}}_lexer_EOFs) ? {{PREFIX}}_lexer_EOFs[l] : 0;
		}
		
		b = l < N({{PREFIX}}_lexer_accepts) ? {{PREFIX}}_lexer_accepts[l] : 0;
		
		#ifdef ZEBU_DEBUG
		ddprintf(this, "lexer: \"%.*s\" (%u): a = %u, b = %u\n", this->l.n, this->l.data, i, a, b);
		#endif
		
		if (a)
		{
			if (b)
			{
				l = a, t = b, f = i++;
			}
			else
			{
				l = a, i++;
			}
		}
		else if (b)
		{
			if (!this->l.n)
			{
				#ifdef ZEBU_DEBUG
				ddprintf(this, "lexer: EOF.\n");
				#endif
				process_token(this, b, NULL);
				break;
			}
			else if (b == 1)
			{
				#ifdef ZEBU_DEBUG
				ddprintf(this, "lexer: whitespace: \"%.*s\"\n", i, this->l.data);
				#endif
				
				memmove(this->l.data, this->l.data + i, this->l.n - i), this->l.n -= i;
				
				l = bl, t = 0, i = 0;
			}
			else
			{
				#ifdef ZEBU_DEBUG
				ddprintf(this, "lexer: token: \"%.*s\"\n", i, this->l.data);
				#endif
				
				struct {{PREFIX}}_token* token = malloc(sizeof(*token));
				token->refcount = 1;
				token->data = memcpy(malloc(i + 1), this->l.data, i);
				token->len = i;
				token->data[i] = 0;
				
				process_token(this, b, token);
				
				memmove(this->l.data, this->l.data + i, this->l.n - i), this->l.n -= i;
				
				l = {{PREFIX}}_lexer_starts[this->y.data[this->y.n - 1]], f = 0, t = 0, i = 0;
			}
		}
		else if (f)
		{
			assert(t);
			assert(!"256");
			#if 0
			process_token(this, t);
			l = {{PREFIX}}_starts[this->y.data[this->y.n - 1]], i = f, t = 0;
			#endif
		}
		else
		{
			assert(!"TODO");
		}
	}
	
	assert(this->d.n == 1);
	
	struct zebu_$start* root = this->d.data[0];
	
	#ifdef ZEBU_DEBUG
	print_{{PREFIX}}_$start(NULL, p_root, "start", root);
	#endif
	
	return root;
}

void free_{{PREFIX}}_state(struct {{PREFIX}}_state* this)
{
	if (this)
	{
		free(this->y.data);
		free(this->d.data);
		free(this->l.data);
		free(this);
	}
}












