
#include "node_type.h"

struct structinfo_node
{
	struct string* name;
	
	enum structinfo_node_type type;
	
	union
	{
		struct {
			struct string* name;
		} grammar;
		
		struct {
			struct format_flags* fflags;
		} scanf;
		
		struct {
			struct structinfo* structinfo;
		} substructinfo;
		
		struct {
			struct string* type;
			struct string* destructor;
		} user_defined;
	};
	unsigned refcount;
};

