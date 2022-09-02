
struct structinfo_node
{
	struct string* name;
	
	enum {
		sin_token,
		sin_grammar
	} kind;
	
	union {
		struct {
		
		} token;
		struct {
			struct string* name;
		} grammar;
	};
};

