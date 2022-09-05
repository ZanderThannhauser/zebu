
#include <debug.h>

#include "struct.h"
#include "to_string.h"

char* reductioninfo_to_string(struct reductioninfo* info)
{
	ENTER;
	
	TODO;
	#if 0
	struct {
		char* data;
		unsigned n, cap;
	} buffer = {};
	
	void append(const char* str)
	{
		unsigned len = strlen(str);
		
		while (buffer.n + len >= buffer.cap)
		{
			buffer.cap = buffer.cap << 1 ?: 1;
			buffer.data = srealloc(buffer.data, buffer.cap);
		}
		
		memcpy(buffer.data + buffer.n, str, len + 1);
		buffer.n += len;
	}
	
	void helper(struct reductioninfo* info)
	{
		if (info)
		{
			helper(info->prev);
			
			char temp[100];
			
			snprintf(temp, 100, " | @[%u] = ", info->index);
			
			append(temp), append(info->tag->chars);
		}
	}
	
	helper(info);
	
	dpvs(buffer.data);
	
	EXIT;
	return buffer.data;
	#endif
}











