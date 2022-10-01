
{{PARSE_TREE_STRUCTS}}

{{PARSE_TREE_INC_FUNCTIONS}}

{{PARSE_TREE_FREE_FUNCTIONS}}

struct {{PREFIX}}_state;

struct {{PREFIX}}_state* new_{{PREFIX}}_state();

void {{PREFIX}}_reset(struct {{PREFIX}}_state* this);

void {{PREFIX}}_parse(struct {{PREFIX}}_state* this,
	const unsigned char* buffer,
	unsigned len);

struct zebu_$start* {{PREFIX}}_close(struct {{PREFIX}}_state* this);

void free_{{PREFIX}}_state(struct {{PREFIX}}_state* this);



