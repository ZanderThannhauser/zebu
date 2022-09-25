
struct structinfo_node;

void structinfo_foreach(
	struct structinfo* this,
	void (*runme)(struct structinfo_node* ele));
