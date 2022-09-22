
struct string;

void structinfo_add_user_defined_field(
	struct structinfo* this,
	struct string* type,
	struct string* name,
	struct string* destructor);
