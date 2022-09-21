
#include <assert.h>

#include <debug.h>

/*#include <avl/search.h>*/
/*#include <avl/insert.h>*/

#include <regex/set_kind.h>
#include <regex/free.h>

#include "to_node/struct.h"
#include "to_node/new.h"

#include "from_node/new.h"

#include "struct.h"

#include "add_token.h"

unsigned lex_add_token(
	struct lex* this,
	struct regex* token,
	enum token_kind token_kind)
{
	unsigned retval;
	ENTER;
	
	dpv(token);
	
	dpv(token_kind);
	
	struct avl_node_t* node;
	
	if ((node = avl_search(this->dfa_to_id, &token)))
	{
		struct dfa_to_id_node* found = node->item;
		
		free_regex(token);
		
		retval = found->id;
	}
	else
	{
		regex_set_kind(token, retval = this->next_id++, token_kind);
		
		struct dfa_to_id_node*   to   =   new_dfa_to_id_node(retval, token);
		struct dfa_from_id_node* from = new_dfa_from_id_node(retval, token);
		
		avl_insert(this->dfa_to_id,   to);
		avl_insert(this->dfa_from_id, from);
	}
	
	dpv(retval);
	
	EXIT;
	return retval;
}













