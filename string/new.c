
#include <debug.h>

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

struct string* new_string_from_tokenchars(struct tokenizer* tokenizer)
{
	return new_string((const char*) tokenizer->tokenchars.chars);
}
