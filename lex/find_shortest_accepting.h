
struct fsa_rettype {
	unsigned char* data;
	unsigned len;
} lex_find_shortest_accepting(
	struct lex_state* source,
	struct unsignedset* acceptme);
