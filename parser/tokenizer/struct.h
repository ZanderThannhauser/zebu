
#include "../token.h"

struct tokenizer
{
	int fd;
	
	struct {
		char data[4096];
		size_t i, n;
	} buffer;
	
	char c;
	
	struct {
		char* chars;
		size_t n, cap;
	} tokenchars;
	
	enum token token;
};

