
struct regex;

struct regex_transition
{
	unsigned char value;
	struct regex* to;
};
