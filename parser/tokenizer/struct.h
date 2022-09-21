
#include <stddef.h>

#include "token.h"

struct tokenizer
{
	int fd;
	
	struct {
		unsigned char data[4096];
		size_t i, n;
	} buffer;
	
	unsigned line;
	
	char c;
	
	struct {
		unsigned char* chars;
		size_t n, cap;
	} tokenchars;
	
	enum token token;
};

