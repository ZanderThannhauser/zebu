
#ifndef STRUCT_STRUCTINFO_NODE_KIND
#define STRUCT_STRUCTINFO_NODE_KIND

enum structinfo_node_type
{
	snt_token_scalar,
	snt_token_array,
	
	snt_grammar_scalar,
	snt_grammar_array,
	
	snt_scanf_scalar,
	snt_scanf_array,
	
	snt_substructinfo_scalar,
	snt_substructinfo_array,
	
	snt_user_defined,
};

#endif
