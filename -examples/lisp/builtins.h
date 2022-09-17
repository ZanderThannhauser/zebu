
struct value* and_builtin(struct scope* scope, struct value** parameters, unsigned n);

struct value* or_builtin(struct scope* scope, struct value** parameters, unsigned n);

struct value* bool_builtin(struct scope* scope, struct value** parameters, unsigned n);


struct value* sum_builtin(struct scope* scope, struct value** parameters, unsigned n);

struct value* subtract_builtin(struct scope* scope, struct value** parameters, unsigned n);

struct value* product_builtin(struct scope* scope, struct value** parameters, unsigned n);

struct value* mod_builtin(struct scope* scope, struct value** parameters, unsigned n);

struct value* divide_builtin(struct scope* scope, struct value** parameters, unsigned n);

struct value* expo_builtin(struct scope* scope, struct value** parameters, unsigned n);


struct value* less_builtin(struct scope* scope, struct value** parameters, unsigned n);

struct value* greater_builtin(struct scope* scope, struct value** parameters, unsigned n);

struct value* equals_builtin(struct scope* scope, struct value** parameters, unsigned n);


struct value* strconcat_builtin(struct scope* scope, struct value** parameters, unsigned argc);


struct value* concat_builtin(struct scope* scope, struct value** parameters, unsigned n);

struct value* prepend_builtin(struct scope* scope, struct value** parameters, unsigned n);

struct value* append_builtin(struct scope* scope, struct value** parameters, unsigned n);

struct value* map_builtin(struct scope* scope, struct value** parameters, unsigned argc);

struct value* list_builtin(struct scope* scope, struct value** parameters, unsigned argc);

struct value* range_builtin(struct scope* scope, struct value** parameters, unsigned argc);

struct value* filter_builtin(struct scope* scope, struct value** parameters, unsigned argc);

struct value* reduce_builtin(struct scope* scope, struct value** parameters, unsigned argc);

struct value* first_builtin(struct scope* scope, struct value** parameters, unsigned argc);

struct value* len_builtin(struct scope* scope, struct value** parameters, unsigned argc);


struct value* lambda_builtin(struct scope* scope, struct value** parameters, unsigned argc);

struct value* define_builtin(struct scope* scope, struct value** parameters, unsigned argc);

struct value* if_builtin(struct scope* scope, struct value** parameters, unsigned argc);


