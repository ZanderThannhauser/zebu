
#include <string.h>
/*#include <memory/srealloc.h>*/

#include <debug.h>

#include "strfandr.h"

char* strfandr(
	const char* original,
	const char* findme,
	const char* replacewith)
{
	ENTER;
	
	TODO;
	#if 0
	struct {
		char* data; unsigned n, cap;
	} buffer = {};
	
	void concat(const char* start, unsigned length) {
		ENTER;
		dpvsn(start, length);
		while (buffer.n + length >= buffer.cap) {
			buffer.cap = buffer.cap << 1 ?: 1;
			dpv(buffer.cap);
			buffer.data = srealloc(buffer.data, buffer.cap);
		}
		memcpy(buffer.data + buffer.n, start, length);
		buffer.n += length;
		dpv(buffer.n);
		EXIT;
	}
	
	size_t strlen_findme = strlen(findme);
	size_t strlen_replacewith = strlen(replacewith);
	size_t strlen_original = strlen(original);
	
	const char* l = original;
	
	for (const char* f; (f = strstr(l, findme));)
	{
		concat(l, f - l);
		concat(replacewith, strlen_replacewith);
		f += strlen_findme, l = f;
	}
	
	concat(l, (original + strlen_original + 1) - l);
	
	dpvs(buffer.data);
	
	EXIT;
	return buffer.data;
	#endif
}













