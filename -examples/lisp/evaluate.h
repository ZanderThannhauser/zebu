
struct scope;

struct value* evaluate_function(
	struct scope* scope,
	struct value* function,
	struct value** parameters, unsigned argc);
	
struct value* evaluate(struct scope* scope, struct value* value);

