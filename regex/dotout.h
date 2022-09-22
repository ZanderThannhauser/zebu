
struct ptrset;

struct regex;

void regex_dotout(struct regex* state, const char* name);

void regex_dotout_set(struct ptrset* set, const char* name);

void regex_dotout_two_nodes(struct regex* a, struct regex* b, const char* name);
