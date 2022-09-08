
struct build_tokenizer_node
{
	struct unsignedset* given; // "owned"
	
	struct unsignedsetset* matches; // "owned"
	
	struct lex_state* start; // yacc_state will free this
};

