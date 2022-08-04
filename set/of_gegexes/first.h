
struct gegex* gegexset_first(
	const struct gegexset* this,
	bool (*runme)(struct gegex* state, va_list*), ...);
