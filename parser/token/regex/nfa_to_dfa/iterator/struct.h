
struct iterator
{
	struct transition **moving, **end;
	
	struct regex* default_to;
	
	unsigned last_used;
};

