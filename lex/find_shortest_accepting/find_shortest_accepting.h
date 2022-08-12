
struct lfsa_rettype {
	unsigned char* data;
	unsigned len;
} lex_find_shortest_accepting(
	struct lex_state* start,
	struct tokenset* acceptme);
