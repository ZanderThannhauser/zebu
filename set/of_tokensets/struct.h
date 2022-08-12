
struct tokensetset
{
	struct tokenset** data; // do I own these? tell free()
	
	unsigned cap, n;
};

