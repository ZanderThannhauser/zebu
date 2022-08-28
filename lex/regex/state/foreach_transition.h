void regex_foreach_transition(
	struct regex* this,
	void (*runme)(unsigned char value, struct regex* to)
);
