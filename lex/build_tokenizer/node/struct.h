
struct build_tokenizer_node
{
	struct tokenset* given; // free me, must be first
	
	struct tokensetset* matches; // free me
	struct lex_state* start;
};

