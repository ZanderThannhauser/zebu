
struct fragment
{
	char* name; // free me
	struct regex_state* start; // but not me
};

