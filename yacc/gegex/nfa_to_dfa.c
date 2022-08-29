
#include <debug.h>

#include <yacc/gegex/state/new.h>

#ifdef VERBOSE
#include <quack/struct.h>
#include <misc/default_sighandler.h>
#endif

#include "nfa_to_dfa.h"

struct mapping
{
	struct gegexset* stateset; // must be the first
	
	struct gegex* combined_state;
};

static struct mapping* new_mapping(
	struct gegexset* stateset,
	struct gegex* state)
{
	ENTER;
	
	struct mapping* this = smalloc(sizeof(*this));
	
	this->stateset = stateset;
	
	this->combined_state = state;
	
	EXIT;
	return this;
}

static int compare_mappings(const void* a, const void* b)
{
	const struct mapping *A = a, *B = b;
	TODO;
	#if 0
	return compare_gegexsets(A->stateset, B->stateset);
	#endif
}

static void free_mapping(void* a)
{
	struct mapping* this = a;
	ENTER;
	
	TODO;
	#if 0
	free_gegexset(this->stateset);
	#endif
	
	free(this);
	
	EXIT;
}

static void add_lambda_states(struct gegexset* set, struct gegex* ele)
{
	ENTER;
	
	TODO;
	#if 0
	if (gegexset_add(set, ele))
	{
		for (unsigned i = 0, n = ele->lambda_transitions.n; i < n; i++)
		{
			add_lambda_states(set, ele->lambda_transitions.data[i]);
		}
	}
	#endif
	
	EXIT;
}

struct gegex* gegex_nfa_to_dfa(struct gegex* original_start)
{
	ENTER;
	
	struct quack* todo = new_quack();
	
	struct avl_tree_t* mappings = avl_alloc_tree(compare_mappings, free_mapping);
	
	struct gegex* new_start = new_gegex();
	
	{
		TODO;
		#if 0
		struct gegexset* start_set = new_gegexset();
		
		add_lambda_states(start_set, original_start);
		
		struct mapping* mapping = new_mapping(start_set, new_start);
		
		quack_append(todo, mapping);
		
		avl_insert(mappings, mapping);
		#endif
	}
	
	#ifdef VERBOSE
	unsigned completed = 0;
	
	void handler(int _)
	{
		char buffer[1000] = {};
		
		unsigned total = completed + todo->n;
		
		size_t len = snprintf(buffer, sizeof(buffer),
			"\e[k" "%s: gegex nfa-to-dfa: %u of %u (%.2f%%)\r", argv0,
				completed, total, (double) completed * 100 / total);
		
		if (write(1, buffer, len) != len)
		{
			abort();
		}
	}
	
	signal(SIGALRM, handler);
	#endif
	
	#ifdef DOTOUT
	gegex_dotout(new_start, __PRETTY_FUNCTION__);
	#endif
	
	while (quack_len(todo))
	{
		dpv(todo->n);
		
		#ifdef VERBOSE
		completed++;
		#endif
		
		struct mapping* mapping = quack_pop(todo);
		
		struct gegexset* const stateset = mapping->stateset;
		
		struct gegex* const state = mapping->combined_state;
		
		TODO;
		#if 0
		// set this as reduction_point if any states in list are accepting:
		{
			bool is_reduction_point = false;
			
			gegextree_foreach(states, ({
				void runme(struct gegex* ele) {
					if (ele->is_reduction_point) {
						is_reduction_point = true;
					}
				}
				runme;
			}));
			
			state->is_reduction_point = is_reduction_point;
			
			dpvb(state->is_reduction_point);
		}
		
		#ifdef WITH_ARENAS
		unsigned (*indexes)[len(states)] = arena_malloc(arena, sizeof(*indexes));
		#else
		unsigned (*indexes)[len(states)] = malloc(sizeof(*indexes));
		#endif
		
		memset(*indexes, 0, sizeof(*indexes));
		
		#ifdef WITH_ARENAS
		struct gegextree* subset = new_gegextree(arena);
		#else
		struct gegextree* subset = new_gegextree();
		#endif
		
		bool assigned;
		unsigned token;
		
		while (({
			assigned = false;
			gegextree_enumerate(states, ({
				void runme(unsigned i, struct gegex* state) {
					unsigned index = (*indexes)[i];
					if (index < state->transitions.n) {
						struct gegex* const to = state->transitions.data[index]->to;
						unsigned ele_token = state->transitions.data[index]->token;
						if (!assigned || ele_token < token) {
							gegextree_clear(subset);
							gegex_add_lamda_states(subset, to);
							token = ele_token;
							assigned = true;
						} else if (token == ele_token) {
							gegex_add_lamda_states(subset, to);
						}
					}
				}
				runme;
			}));
			assigned;
		})) {
			dpv(token);
			dpv(len(subset));
			
			struct gegex* to = gegex_nfa_to_dfa_helper(
				#ifdef VERBOSE
				node_count,
				#endif
				#ifdef WITH_ARENAS
				arena,
				#endif
				subset, mappings);
			
			gegex_add_transition(state, token, to);
			
			// move forward all indexes that whose ele_token == token
			gegextree_enumerate(states, ({
				void runme(unsigned i, struct gegex* state) {
					unsigned index = (*indexes)[i];
					if (index < state->transitions.n && token == state->transitions.data[index]->token) {
						(*indexes)[i]++;
					}
				}
				runme;
			}));
		}
		
		memset(*indexes, 0, sizeof(*indexes));
		
		char* grammar;
		while (({
			assigned = false;
			gegextree_enumerate(states, ({
				void runme(unsigned i, struct gegex* state) {
					unsigned index = (*indexes)[i];
					if (index < state->grammar_transitions.n) {
						struct gegex* const to = state->grammar_transitions.data[index]->to;
						char* ele_grammar = state->grammar_transitions.data[index]->grammar;
						int cmp;
						if (!assigned || (cmp = strcmp(ele_grammar, grammar)) < 0) {
							gegextree_clear(subset);
							gegex_add_lamda_states(subset, to);
							grammar = ele_grammar;
							assigned = true;
						} else if (!cmp) {
							gegex_add_lamda_states(subset, to);
						}
					}
				}
				runme;
			}));
			assigned;
		})) {
			dpvs(grammar);
			dpv(len(subset));
			
			struct gegex* to = gegex_nfa_to_dfa_helper(
				#ifdef VERBOSE
				node_count,
				#endif
				#ifdef WITH_ARENAS
				arena,
				#endif
				subset, mappings);
			
			#ifdef WITH_ARENAS
			char* dup = arena_strdup(arena, grammar);
			#else
			char* dup = strdup(grammar);
			#endif
			
			gegex_add_grammar_transition(state, dup, to);
			
			// move forward all indexes that whose ele_token == token
			gegextree_enumerate(states, ({
				void runme(unsigned i, struct gegex* state) {
					unsigned index = (*indexes)[i];
					if (index < state->grammar_transitions.n && strequals(grammar, state->grammar_transitions.data[index]->grammar))
						(*indexes)[i]++;
				}
				runme;
			}));
		}
		
		free_gegextree(subset);
		
		#ifdef WITH_ARENAS
		arena_dealloc(arena, indexes);
		#else
		free(indexes);
		#endif
		
		#endif
		
		#ifdef DOTOUT
		gegex_dotout(new_start, __PRETTY_FUNCTION__);
		#endif
	}
	
	#ifdef VERBOSE
	signal(SIGALRM, default_sighandler);
	#endif
	
	avl_free_tree(mappings);
	
	free_quack(todo);
	
	EXIT;
	return new_start;
}






















