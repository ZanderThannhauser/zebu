
#if 0
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>
#include <arena/realloc.h>
#include <arena/dealloc.h>

#include <set/of_tokens/struct.h>
#include <set/of_tokens/new.h>
#include <set/of_tokens/contains.h>
#include <set/of_tokens/update.h>
#include <set/of_tokens/add.h>
#include <set/of_tokens/clone.h>
#include <set/of_tokens/free.h>

#ifdef DEBUGGING
#include <set/of_tokens/print.h>
#endif

#include <parser/options/dlink.h>

#include "regex/state/struct.h"
#include "regex/state/accepts.h"

#include "lookup/id_to_dfa.h"

#include <misc/phase_counters.h>
#include "struct.h"
#include "process_disambiguatations.h"

struct tokenset_array
{
	struct tokenset** data;
	unsigned n, cap;
	
	#ifdef WITH_ARENAS
	struct memory_arena* arena;
	#endif
};

static struct tokenset_array* new_tokenset_array(
	#ifdef WITH_ARENAS
	struct memory_arena* arena
	#endif
) {
	ENTER;
	
	#ifdef WITH_ARENAS
	struct tokenset_array* this = arena_malloc(arena, sizeof(*this));
	this->arena = arena;
	#else
	struct tokenset_array* this = malloc(sizeof(*this));
	#endif
	
	this->data = NULL;
	this->n = 0, this->cap = 0;
	
	EXIT;
	return this;
}

static void tokenset_array_append(struct tokenset_array* this, struct tokenset* ele)
{
	ENTER;
	
	if (this->n + 1 >= this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		
		dpv(this->cap);
		
		#ifdef WITH_ARENAS
		this->data = arena_realloc(this->arena, this->data, sizeof(*this->data) * this->cap);
		#else
		this->data = realloc(this->data, sizeof(*this->data) * this->cap);
		#endif
	}
	
	this->data[this->n++] = ele;
	
	EXIT;
}

static void free_tokenset_array(struct tokenset_array* this)
{
	ENTER;
	
	for (unsigned i = 0, n = this->n; i < n; i++)
	{
		free_tokenset(this->data[i]);
	}
	
	#ifdef WITH_ARENAS
	arena_dealloc(this->arena, this);
	#else
	free(this);
	#endif
	
	EXIT;
}

static struct tokenset_array* msort(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	struct tokenset** unsorted, unsigned n,
	int (*compare)(unsigned, unsigned))
{
	ENTER;
	
	dpv(n);
	
	#ifdef WITH_ARENAS
	struct tokenset_array* retval = new_tokenset_array(arena);
	#else
	struct tokenset_array* retval = new_tokenset_array();
	#endif
	
	if (n < 2)
	{
		assert(n == 1);
		
		#ifdef WITH_ARENAS
		tokenset_array_append(retval, tokenset_clone(arena, unsorted[0]));
		#else
		tokenset_array_append(retval, tokenset_clone(unsorted[0]));
		#endif
	}
	else
	{
		unsigned m = n / 2;
		
		#ifdef WITH_ARENAS
		struct tokenset_array* left = msort(arena, unsorted, m, compare);
		struct tokenset_array* right = msort(arena, unsorted + m, n - m, compare);
		#else
		struct tokenset_array* left = msort(unsorted, m, compare);
		struct tokenset_array* right = msort(unsorted + m, n - m, compare);
		#endif
		
		struct { unsigned i, n; } l = {0, left->n}, r = {0, right->n};
		
		while (l.i < l.n && r.i < r.n)
		{
			struct tokenset* lele = left->data[l.i];
			struct tokenset* rele = right->data[r.i];
			
			assert(lele->n > 0);
			assert(rele->n > 0);
			
			int cmp = compare(lele->data[0], rele->data[0]);
			
			dpv(cmp);
			
			#ifdef WITH_ARENAS
			struct tokenset* new = new_tokenset(arena);
			#else
			struct tokenset* new = new_tokenset();
			#endif
			
			if (cmp > 0)
				tokenset_update(new, rele), r.i++;
			else if (cmp < 0)
				tokenset_update(new, lele), l.i++;
			else
			{
				tokenset_update(new, lele), l.i++;
				tokenset_update(new, rele), r.i++;
			}
			
			tokenset_array_append(retval, new);
		}
		
		while (l.i < l.n)
		{
			#ifdef WITH_ARENAS
			tokenset_array_append(retval, tokenset_clone(arena, left->data[l.i++]));
			#else
			tokenset_array_append(retval, tokenset_clone(left->data[l.i++]));
			#endif
		}
		
		while (r.i < r.n)
		{
			#ifdef WITH_ARENAS
			tokenset_array_append(retval, tokenset_clone(arena, right->data[r.i++]));
			#else
			tokenset_array_append(retval, tokenset_clone(right->data[r.i++]));
			#endif
		}
		
		free_tokenset_array(left);
		free_tokenset_array(right);
	}
	
	EXIT;
	return retval;
}

void lex_process_disambiguatations(
	struct lex* this,
	struct dlink* head)
{
	ENTER;
	
	int compare(unsigned lid, unsigned rid)
	{
		struct dlink* moving = head;
		ENTER;
		
		dpv(lid);
		dpv(rid);
		
		while (moving)
		{
			dpv(moving);
			
			bool matches(const struct dop* op, unsigned id)
			{
				dpv(id);
				
				switch (op->kind)
				{
					case dk_literal:
						return tokenset_contains(this->disambiguations.literal_ids, id);
					
					case dk_regex:
						return tokenset_contains(this->disambiguations.regex_ids, id);
					
					case dk_string:
					{
						CHECK;
						struct regex* dfa = lex_id_to_dfa(this, id);
						return regex_accepts(dfa, op->s.chars, op->s.len);
					}
					
					default: TODO; break;
				}
			}
			
			if (matches(&moving->left, lid) && matches(&moving->right, rid))
			{
				int cmp = moving->cmp;
				dpv(cmp);
				EXIT;
				return cmp;
			}
			else if (matches(&moving->right, lid) && matches(&moving->left, rid))
			{
				int cmp = -moving->cmp;
				dpv(cmp);
				EXIT;
				return cmp;
			}
			else
			{
				moving = moving->next;
			}
		}
		
		EXIT;
		return 0;
	}
	
	dpv(this->next_id);
	
	#ifdef WITH_ARENAS
	struct memory_arena* const arena = this->arena;
	struct tokenset_array* original = new_tokenset_array(arena);
	#else
	struct tokenset_array* original = new_tokenset_array();
	#endif
	
	for (unsigned i = 1, n = this->next_id; i < n; i++)
	{
		#ifdef WITH_ARENAS
		struct tokenset* ts = new_tokenset(arena);
		#else
		struct tokenset* ts = new_tokenset();
		#endif
		
		tokenset_add(ts, i);
		tokenset_array_append(original, ts);
	}
	
	#ifdef WITH_ARENAS
	struct tokenset_array* sorted = msort(arena, original->data, original->n, compare);
	#else
	struct tokenset_array* sorted = msort(original->data, original->n, compare);
	#endif
	
	dpv(original->n);
	
	dpv(this->disambiguations.literal_ids->n);
	dpv(this->disambiguations.regex_ids->n);
	
	dpv(sorted->n);
	
	lex_phase_counter++;
	
	for (unsigned i = 0, n = sorted->n; i < n; i++)
	{
		dpv(sorted->data[i]->n);
		
		for (unsigned j = 0, m = sorted->data[i]->n; j < m; j++)
		{
			dpv(j);
			
			struct regex* dfa = lex_id_to_dfa(this, sorted->data[i]->data[j]);
			
			void helper(struct regex* state)
			{
				if (state->phase != lex_phase_counter)
				{
					state->phase = lex_phase_counter;
					
					state->priority = i;
					
					for (unsigned k = 0, o = state->transitions.n; k < o; k++)
						helper(state->transitions.data[k]->to);
					
					assert(!state->lambda_transitions.n);
					
					if (state->default_transition_to)
						helper(state->default_transition_to);
				}
			}
			
			helper(dfa);
		}
	}
	
	free_tokenset_array(original);
	free_tokenset_array(sorted);
	
	EXIT;
}



















#endif
