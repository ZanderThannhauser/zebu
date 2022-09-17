
struct value;
struct scope;

struct scope* new_scope(struct scope* prev);

void scope_define_builtins(struct scope* this);

void scope_push(struct scope* this);

void scope_pop(struct scope* this);

struct value* scope_lookup(struct scope* this, const char* value);

void scope_define(struct scope* this, const char* name, struct value* value);

void free_scope(struct scope* this);


