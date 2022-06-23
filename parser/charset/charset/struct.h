
struct charset
{
	char* chars;
	size_t len;
	
	bool is_complement;
	
	unsigned refcount;
};

