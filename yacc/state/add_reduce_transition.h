
void yacc_state_add_reduce_transition(
	struct yacc_state* this,
	struct unsignedset* on,
	struct string* reduce_as,
	unsigned popcount,
	struct reductioninfo* reductioninfo,
	struct structinfo* structinfo);
