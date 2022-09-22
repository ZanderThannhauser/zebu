
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <parser/tokenizer/struct.h>

#include "struct.h"
#include "new.h"

struct string* new_string_without_copy(char* str)
{
	ENTER;
	
	dpvs(str);
	
	struct string* this = smalloc(sizeof(*this));
	
	this->chars = str;
	this->len = strlen(str);
	this->refcount = 1;
	
	EXIT;
	return this;
}

struct string* new_string(const char* str)
{
	return new_string_without_copy(strdup(str));
}

struct string* new_string_len(const char* str, unsigned len)
{
	return new_string_without_copy(strndup(str, len));
}

struct string* new_string_from_tokenchars(struct tokenizer* tokenizer)
{
	return new_string_len((const char*) tokenizer->tokenchars.chars, tokenizer->tokenchars.n);
}

struct string* new_string_from_format(const char* fmt, ...)
{
	ENTER;
	
	va_list ap;
	
	va_start(ap, fmt);
	
	char* chars;
	
	if (vasprintf(&chars, fmt, ap) < 0)
		abort();
	
	dpvs(chars);
	
	struct string* this = new_string_without_copy(chars);
	
	va_end(ap);
	
	EXIT;
	return this;
}

































