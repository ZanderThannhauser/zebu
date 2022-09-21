
struct unsignedset;
struct structinfo;
struct gegex;

void gegex_add_transition(
	struct gegex* from,
	unsigned token,
	struct unsignedset* whitespace,
	struct structinfo* structinfo,
	struct gegex* to);
