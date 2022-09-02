
#ifndef STRUCT_STRING_H
#define STRUCT_STRING_H

struct string
{
	char* chars; // I own this
	unsigned len, refcount;
};


#endif
