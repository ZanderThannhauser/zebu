
#ifndef STRUCT_NAMED_TOKENSET
#define STRUCT_NAMED_TOKENSET

struct named_tokenset
{
	const char* name;
	struct tokenset* tokenset;
};

#endif
