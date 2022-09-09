
#include <debug.h>

#include <memory/smalloc.h>
#include <memory/srealloc.h>

#include "struct.h"
#include "add_transition.h"

void trie_add_transition(
	struct trie* this,
	unsigned token,
	struct trie* to)
{
	ENTER;
	
	if (this->transitions.n == this->transitions.cap)
	{
		this->transitions.cap = this->transitions.cap << 1 ?: 1;
		
		this->transitions.data = srealloc(this->transitions.data,
			sizeof(*this->transitions.data) * this->transitions.cap);
	}
	
	struct trie_transition* transition = smalloc(sizeof(*transition));
	
	transition->token = token;
	
	transition->to = to;
	
	unsigned i;
	struct trie_transition** const data = this->transitions.data;
	
	dpv(data);
	
	for (i = this->transitions.n - 1; 0 + 1 <= i + 1 && token < data[i]->token; i--)
	{
		dpv(i);
		
		data[i + 1] = data[i];
	}
	
	dpv(i);
	
	data[i + 1] = transition, this->transitions.n++;
	
	dpv(this->transitions.n);
	
	EXIT;
}






