
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include <debug.h>

/*#include <memory/smalloc.h>*/

#include <avl/search.h>
#include <avl/insert.h>
#include <avl/free_tree.h>

#include <heap/new.h>
#include <heap/free.h>
#include <heap/push.h>
#include <heap/pop.h>
#include <heap/len.h>

#include <macros/len.h>

#include "../state/struct.h"

#include "find_shortest_accepting.h"

#include <misc/phase_counters.h>

#ifdef DEBUGGING

#include <misc/escape.h>
#include <misc/frame_counter.h>
#include <set/of_tokens/to_string.h>


struct dist_node
{
	const struct lex_state* state;
	unsigned dist;
};

static int compare_dist_nodes(const void* a, const void* b)
{
	const struct dist_node* A = a, *B = b;
	if (A->state > B->state)
		return +1;
	else if (A->state < B->state)
		return -1;
	else
		return +0;
}

static bool has_dist(
	struct avl_tree_t* tree,
	const struct lex_state* state)
{
	return !!avl_search(tree, &state);
}

static void set_dist(
	struct avl_tree_t* tree,
	const struct lex_state* state, unsigned dist)
{
	TODO;
	#if 0
	struct avl_node_t* node = avl_search(tree, &state);
	if (node)
	{
		struct dist_node* old = node->item;
		old->dist = dist;
	}
	else
	{
		struct dist_node* new = smalloc(sizeof(*new));
		new->state = state, new->dist = dist;
		avl_insert(tree, new);
	}
	#endif
}

static unsigned get_dist(
	struct avl_tree_t* tree,
	const struct lex_state* state)
{
	struct avl_node_t* node = avl_search(tree, &state);
	assert(node);
	struct dist_node* old = node->item;
	return old->dist;
}

struct prev_node
{
	struct lex_state* state;
	struct lex_state* prev;
	unsigned char value;
};

static int compare_prev_nodes(const void* a, const void* b)
{
	const struct prev_node *A = a, *B = b;
	if (A->state > B->state)
		return +1;
	else if (A->state < B->state)
		return -1;
	else
		return +0;
}

static void set_prev(
	struct avl_tree_t* tree,
	struct lex_state* state,
	struct lex_state* prev,
	unsigned char value)
{
	struct avl_node_t* node = avl_search(tree, &state);
	if (node)
	{
		struct prev_node* old = node->item;
		old->prev = prev;
		old->value = value;
	}
	else
	{
		TODO;
		#if 0
		struct prev_node* new = smalloc(sizeof(*new));
		new->state = state;
		new->prev = prev;
		new->value = value;
		avl_insert(tree, new);
		#endif
	}
}

static struct lex_state* get_prev(
	struct avl_tree_t* tree,
	struct lex_state* state,
	unsigned char* out_value)
{
	struct avl_node_t* node = avl_search(tree, &state);
	if (node)
	{
		struct prev_node* old = node->item;
		*out_value = old->value;
		return old->prev;
	}
	else
	{
		return NULL;
	}
}

static void helper(FILE* out, struct lex_state* state,
	struct avl_tree_t* dist,
	unsigned max_dist)
{
	ENTER;
	
	if (state->phase != lex_phase_counter)
	{
		size_t i, n;
		
		state->phase = lex_phase_counter;
		
		{
			char* label = NULL;
			
			if (state->accepting)
				label = tokenset_to_string(state->accepting);
			
			if (has_dist(dist, state))
			{
				fprintf(out, ""
					"\"%p\" [" "\n"
						"\t" "shape = %s;" "\n"
						"\t" "label = \"%s\";" "\n"
						"\t" "style = filled;" "\n"
						"\t" "fillcolor = \"%lf 1 1\";" "\n"
					"]" "\n"
				"", state, state->accepting ? "doublecircle" : "circle",
				label ?: "", (double) get_dist(dist, state) / max_dist);
			}
			else
			{
				fprintf(out, ""
					"\"%p\" [" "\n"
						"\t" "shape = %s;" "\n"
						"\t" "label = \"%s\";" "\n"
					"]" "\n"
				"", state, state->accepting ? "doublecircle" : "circle", label ?: "");
			}
			
			free(label);
		}
		
		// normal transitions:
		for (i = 0, n = state->transitions.n; i < n; i++)
		{
			struct ltransition* transition = state->transitions.data[i];
			
			helper(out, transition->to, dist, max_dist);
			
			unsigned value = transition->value;
			
			dpvc(value);
			
			if (true
				&& i + 1 < n
				&& value + 1 == state->transitions.data[i + 1]->value
				&& transition->to == state->transitions.data[i + 1]->to)
			{
				do i++; while (true
					&& i + 1 < n
					&& state->transitions.data[i]->value + 1 == state->transitions.data[i + 1]->value
					&& transition->to == state->transitions.data[i + 1]->to);
				
				unsigned value2 = state->transitions.data[i]->value;
				
				dpvc(value2);
				
				char low[10], high[10];
				escape(low, value);
				escape(high, value2);
				
				fprintf(out, ""
					"\"%p\" -> \"%p\" [" "\n"
						"\t" "label = \"%s - %s\"" "\n"
					"]" "\n"
				"", state, transition->to, low, high);
			}
			else
			{
				char str[10];
				escape(str, value);
				dpvs(str);
				
				fprintf(out, ""
					"\"%p\" -> \"%p\" [" "\n"
						"\t" "label = \"%s\"" "\n"
					"]" "\n"
				"", state, transition->to, str);
			}
		}
		
		// default transition?:
		if (state->default_transition_to)
		{
			struct lex_state* to = state->default_transition_to;
			
			helper(out, to, dist, max_dist);
			
			fprintf(out, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "label = \"<default>\"" "\n"
				"]" "\n"
			"", state, to);
		}
		
		// EOF transition?
		if (state->EOF_transition_to)
		{
			struct lex_state* to = state->EOF_transition_to;
			
			helper(out, to, dist, max_dist);
			
			fprintf(out, ""
				"\"%p\" -> \"%p\" [" "\n"
					"\t" "label = \"<EOF>\"" "\n"
				"]" "\n"
			"", state, to);
		}
	}
	
	EXIT;
}

static void dotout(
	struct lex_state* state,
	struct avl_tree_t* dist,
	unsigned max_dist)
{
	ENTER;
	
	char path[PATH_MAX];
	
	snprintf(path, PATH_MAX, "dot/find_shortest_accepting-%u.dot", frame_counter++);
	
	dpvs(path);
	
	FILE* out = fopen(path, "w");
	
	if (!out)
	{
		fprintf(stderr, "%s: fopen(\"%s\"): %m\n", argv0, path);
		abort();
	}
	
	fprintf(out, "digraph {" "\n");
	
	fprintf(out, "\t" "rankdir = LR;" "\n");
	
	fprintf(out, "\"%p\" [ style = bold; ];" "\n", state);
	
	lex_phase_counter++;
	
	helper(out, state, dist, max_dist);
	
	fprintf(out, "}" "\n");
	
	if (out)
		fclose(out);
	
	EXIT;
}
#endif

struct lfsa_rettype lex_find_shortest_accepting(
	struct lex_state* source,
	struct tokenset* acceptme)
{
	ENTER;
	
	TODO;
	#if 0
	struct avl_tree_t* dist = new_avl_tree(compare_dist_nodes, free);
	struct avl_tree_t* prev = new_avl_tree(compare_prev_nodes, free);
	
	int compare(const void* a, const void* b)
	{
		const struct lex_state *A = a, *B = b;
		bool a_has_dist = has_dist(dist, A);
		bool b_has_dist = has_dist(dist, B);
		if (a_has_dist > b_has_dist)
			return -1;
		else if (a_has_dist < b_has_dist)
			return +1;
		else if (!a_has_dist)
			return +0;
		else
		{
			unsigned a_dist = get_dist(dist, A), b_dist = get_dist(dist, B);
			if (a_dist > b_dist)
				return +1;
			else if (a_dist < b_dist)
				return -1;
			else
				return +0;
		}
	}
	
	struct heap* Q = new_heap(compare);
	
	set_dist(dist, source, 0);
	
	#ifdef DEBUGGING
	unsigned max_dist = 1;
	#endif
	
	heap_push(Q, source);
	
	while (len(Q))
	{
		struct lex_state* u = heap_pop(Q);
		
		unsigned const alt = get_dist(dist, u) + 1;
		
		for (unsigned i = 0, n = u->transitions.n; i < n; i++)
		{
			struct lex_state* v = u->transitions.data[i]->to;
			
			if (!has_dist(dist, v) || alt < get_dist(dist, v))
			{
				set_dist(dist, v, alt);
				set_prev(prev, v, u, u->transitions.data[i]->value);
				
				heap_push(Q, v);
				
				#ifdef DEBUGGING
				if (alt > max_dist)
					max_dist = alt;
				#endif
			}
		}
		
		if (u->default_transition_to)
		{
			struct lex_state* v = u->default_transition_to;
			
			if (!has_dist(dist, v) || alt < get_dist(dist, v))
			{
				set_dist(dist, v, alt);
				set_prev(prev, v, u, '.');
				
				heap_push(Q, v);
				
				#ifdef DEBUGGING
				if (alt > max_dist)
					max_dist = alt;
				#endif
			}
		}
		
		if (u->EOF_transition_to)
		{
			// TODO;
		}
		
		#ifdef DEBUGGING
		dotout(source, dist, max_dist);
		#endif
	}
	
	unsigned min_dist = 0;
	struct lex_state* target = NULL;
	// search through `dist[]`, looking for accepting node with minimum distance:
	{
		bool found = false;
		
		lex_phase_counter++;
		void helper(struct lex_state* s)
		{
			if (s->phase != lex_phase_counter)
			{
				s->phase = lex_phase_counter;
				
				if (s->accepting == acceptme)
				{
					unsigned ele_dist = get_dist(dist, s);
					
					if (!found || ele_dist < min_dist)
					{
						found = true;
						target = s;
						min_dist = ele_dist;
						dpv(min_dist);
					}
				}
				
				for (unsigned i = 0, n = s->transitions.n; i < n; i++)
					helper(s->transitions.data[i]->to);
				
				if (s->default_transition_to)
					helper(s->default_transition_to);
				
				if (s->EOF_transition_to)
				{
					// TODO;
				}
			}
		}
		
		helper(source);
		
		assert(found);
	}
	
	dpv(min_dist);
	assert(target);
	
	unsigned char* data = smalloc(min_dist);
	
	{
		unsigned char* moving = data;
		
		void helper(struct lex_state* s)
		{
			unsigned char v;
			struct lex_state* p = get_prev(prev, s, &v);
			if (p)
			{
				helper(p);
				dpv(v);
				*moving++ = v;
			}
		}
		
		helper(target);
		assert(moving == data + min_dist);
	}
	
	dpvsn(data, min_dist);
	
	free_heap(Q);
	
	avl_free_tree(dist);
	avl_free_tree(prev);
	
	EXIT;
	return (struct lfsa_rettype) {.data = data, .len = min_dist};
	#endif
}














