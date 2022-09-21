
#include <assert.h>

#include <stdlib.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <string/inc.h>
#include <string/compare.h>
#include <string/are_equal.h>
#include <string/free.h>

#include <avl/search.h>
#include <avl/insert.h>
#include <avl/foreach.h>
#include <avl/alloc_tree.h>
#include <avl/free_tree.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/is_nonempty.h>
#include <quack/pop.h>
#include <quack/free.h>

/*#include <avl/foreach.h>*/

#include <cmdln/minimize_lexer.h>

/*#include <named/gegex/struct.h>*/

#include <lex/struct.h>
#include <lex/build_tokenizer/build_tokenizer.h>
#include <lex/minimize_lexer.h>

#include <set/unsigned/head.h>
#include <set/unsigned/new.h>
#include <set/unsigned/add.h>
#include <set/unsigned/clone.h>
#include <set/unsigned/foreach.h>
#include <set/unsigned/update.h>
#include <set/unsigned/free.h>

#include <set/unsignedset/foreach.h>
#include <set/unsignedset/free.h>

#include <named/gegex/struct.h>

#include <named/trie/struct.h>
#include <named/trie/compare.h>
#include <named/trie/free.h>

#ifdef VERBOSE
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <misc/default_sighandler.h>
#endif

#ifdef DOTOUT
#include "state/dotout.h"
#endif

#include "structinfo/compare.h"
#include "structinfo/free.h"

#include "trie/struct.h"

#include "state/struct.h"
#include "state/new.h"
#include "state/add_transition.h"
#include "state/add_grammar_transition.h"
#include "state/add_reduce_transition.h"

#include "stateinfo/new.h"
#include "stateinfo/add.h"
#include "stateinfo/inc.h"
#include "stateinfo/compare.h"
#include "stateinfo/foreach.h"
#include "stateinfo/free.h"

#include "expand_stateinfo.h"

#include "calc_firsts.h"
#include "build_tries.h"
#include "build_structinfo.h"
#include "yacc.h"

struct mapping
{
	struct stateinfo* stateinfo;
	struct yacc_state* state;
	
	// unsigned hopcount;
	// struct mapping* prev;
};

static struct mapping* new_mapping(
	struct stateinfo* stateinfo,
	struct yacc_state* state)
{
	ENTER;
	
	struct mapping* this = smalloc(sizeof(*this));
	
	this->stateinfo = inc_stateinfo(stateinfo);
	this->state = state;
	
	EXIT;
	return this;
}

static int compare_mappings(const void* a, const void* b)
{
	const struct mapping *A = a, *B = b;
	return compare_stateinfo(A->stateinfo, B->stateinfo);
}

static void free_mapping(void* ptr)
{
	struct mapping* this = ptr;
	
	free_stateinfo(this->stateinfo);
	
	free(this);
}

struct shift_node
{
	unsigned token; // must be the first
	
	struct stateinfo* stateinfo; // "owned" by struct
};

struct reduce_node
{
	unsigned token; // must be the first
	
	struct string* reduce_as;
	
	struct reductioninfo* reductioninfo;
	
	struct structinfo* structinfo;
};

struct subgrammar_node
{
	struct string* grammar; // must be the first
	
	struct stateinfo* stateinfo; // "owned" by struct
};

static struct shift_node* new_shift_node(
	unsigned token)
{
	ENTER;
	
	struct shift_node* this = smalloc(sizeof(*this));
	
	this->token = token;
	
	this->stateinfo = new_stateinfo();
	
	EXIT;
	return this;
}

static int compare_shift_nodes(const void* a, const void* b)
{
	const struct shift_node* A = a, *B = b;
	
	if (A->token > B->token)
		return +1;
	else if (A->token < B->token)
		return -1;
	else
		return 0;
}

static void free_shift_node(void* ptr)
{
	struct shift_node* const this = ptr;
	ENTER;
	
	free_stateinfo(this->stateinfo);
	
	free(this);
	
	EXIT;
}

static struct reduce_node* new_reduce_node(
	unsigned token,
	struct string* reduce_as,
	struct reductioninfo* reductioninfo,
	struct structinfo* structinfo)
{
	ENTER;
	
	struct reduce_node* this = smalloc(sizeof(*this));
	
	this->token = token;
	
	this->reduce_as = inc_string(reduce_as);
	
	this->reductioninfo = reductioninfo;
	
	this->structinfo = structinfo;
	
	EXIT;
	return this;
}

static int compare_reduce_nodes(const void* a, const void* b)
{
	const struct reduce_node* A = a, *B = b;
	
	if (A->token > B->token)
		return +1;
	else if (A->token < B->token)
		return -1;
	else
		return +0;
}

static struct subgrammar_node* new_subgrammar_node(struct string* grammar)
{
	ENTER;
	
	struct subgrammar_node* this = smalloc(sizeof(*this));
	
	this->grammar = inc_string(grammar);
	
	this->stateinfo = new_stateinfo();
	
	EXIT;
	return this;
}

static int compare_subgrammar_nodes(const void* a, const void* b)
{
	const struct subgrammar_node* A = a, *B = b;
	
	return compare_strings(A->grammar, B->grammar);
}

static void free_subgrammar_node(void* ptr)
{
	struct subgrammar_node* const this = ptr;
	ENTER;
	
	free_string(this->grammar);
	
	free_stateinfo(this->stateinfo);
	
	free(this);
	
	EXIT;
}

static void add_shift(
	struct avl_tree_t* shift_tokens,
	unsigned token,
	struct trie* to,
	struct unsignedset* whitespace,
	struct unsignedset* tokens)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(shift_tokens, &token);
	
	struct unsignedset* whitespace_dup = unsignedset_clone(whitespace);
	
	struct unsignedset* tokens_dup = unsignedset_clone(tokens);
	
	if (node)
	{
		struct shift_node* old = node->item;
		
		stateinfo_add(old->stateinfo, to, whitespace_dup, tokens_dup);
	}
	else
	{
		struct shift_node* new = new_shift_node(token);
		
		stateinfo_add(new->stateinfo, to, whitespace_dup, tokens_dup);
		
		avl_insert(shift_tokens, new);
	}
	
	free_unsignedset(whitespace_dup), free_unsignedset(tokens_dup);
	
	EXIT;
}

static void add_reduce(
	struct avl_tree_t* reduce_tokens,
	unsigned token,
	struct string* reduce_as,
	struct reductioninfo* reductioninfo,
	struct structinfo* structinfo)
{
	ENTER;
	
	dpv(token);
	
	struct avl_node_t* node = avl_search(reduce_tokens, &token);
	
	if (node)
	{
		dpvs(reduce_as);
		
		TODO;
		#if 0
		struct reduce_node* old = node->item;
		
		if (strcmp(old->reduce_as, reduce_as))
		{
			dpvs(old->reduce_as);
			dpv(reduce_as);
			
			TODO;
		}
		#endif
	}
	else
	{
		struct reduce_node* new = new_reduce_node(token, reduce_as, reductioninfo, structinfo);
		
		avl_insert(reduce_tokens, new);
	}
	
	EXIT;
}


static void add_subgrammar(
	struct avl_tree_t* subgrammars,
	struct string* grammar,
	struct trie* to,
	struct unsignedset* whitespace,
	struct unsignedset* tokens)
{
	ENTER;
	
	dpvs(grammar);
	
	struct avl_node_t* node = avl_search(subgrammars, &grammar);
	
	struct unsignedset* whitespace_dup = unsignedset_clone(whitespace);
	
	struct unsignedset* tokens_dup = unsignedset_clone(tokens);
	
	if (node)
	{
		struct subgrammar_node* old = node->item;
		
		stateinfo_add(old->stateinfo, to, whitespace_dup, tokens_dup);
	}
	else
	{
		struct subgrammar_node* new = new_subgrammar_node(grammar);
		
		stateinfo_add(new->stateinfo, to, whitespace_dup, tokens_dup);
		
		avl_insert(subgrammars, new);
	}
	
	free_unsignedset(whitespace_dup), free_unsignedset(tokens_dup);
	
	EXIT;
}

struct yacc_state* yacc(
	struct lex* lex,
	struct avl_tree_t* named_gegexes)
{
	ENTER;
	
	struct avl_tree_t* structinfos = avl_alloc_tree(compare_structinfos, free_structinfo);
	
	struct avl_tree_t* named_tries = avl_alloc_tree(compare_named_tries, free_named_trie);
	
	avl_tree_foreach(named_gegexes, ({
		void runme(void* ptr)
		{
			struct named_gegex* named_gegex = ptr;
			
			struct structinfo* structinfo = build_structinfo(named_gegex->name, named_gegex->gegex);
			
			build_tries(named_tries, named_gegex->name, named_gegex->gegex, structinfo);
		}
		runme;
	}));
	
	// node->item are of `struct named_unsignedset*` type.
	struct avl_tree_t* named_firsts = calc_firsts(named_tries);
	
	struct quack* todo = new_quack();
	
	struct avl_tree_t* mappings = avl_alloc_tree(compare_mappings, free_mapping);
	
	struct yacc_state* start = new_yacc_state();
	
	// setup:
	{
		struct stateinfo* stateinfo = new_stateinfo();
		
		struct avl_node_t* node = avl_search(named_tries, &(const char**){(const char*[]) {"$start"}});
		
		if (!node)
		{
			fprintf(stderr, "zebu: the '%%start' directive must be used to specify which grammar starts the parse!\n");
			exit(e_bad_input_file);
		}
		
		struct named_trie* start_trie = node->item;
		
		struct unsignedset* lookahead_whitespace = new_unsignedset();
		
		if (lex->whitespace_token_id)
		{
			unsignedset_add(lookahead_whitespace, lex->whitespace_token_id);
		}
		
		struct unsignedset* lookahead_tokens = new_unsignedset();
		
		unsignedset_add(lookahead_tokens, lex->EOF_token_id);
		
		stateinfo_add(stateinfo, start_trie->trie, lookahead_whitespace, lookahead_tokens);
		
		expand_stateinfo(stateinfo, named_tries, named_firsts);
		
		quack_append(todo, new_mapping(stateinfo, start));
		
		avl_insert(mappings, stateinfo);
		
		free_unsignedset(lookahead_tokens);
		
		free_unsignedset(lookahead_whitespace);
		
		free_stateinfo(stateinfo);
	}
	
	#ifdef VERBOSE
	unsigned completed = 0;
	
	void handler2(int _)
	{
		char buffer[1000] = {};
		
		unsigned total = completed + quack_len(todo);
		
		size_t len = snprintf(buffer, sizeof(buffer),
			"\e[K" "zebu: generate parser: %u of %u (%.2f%%)\r",
				completed, total, (double) completed * 100 / total);
		
		if (write(1, buffer, len) != len)
		{
			abort();
		}
	}
	
	signal(SIGALRM, handler2);
	#endif
	
	while (quack_is_nonempty(todo))
	{
		struct mapping* const mapping = quack_pop(todo);
		
		struct stateinfo* const stateinfo = mapping->stateinfo;
		
		struct yacc_state* const state = mapping->state;
		
		struct unsignedset* all_tokens = new_unsignedset();
		
		struct avl_tree_t* shift_tokens = avl_alloc_tree(compare_shift_nodes, free_shift_node);
		
		struct avl_tree_t* reduce_tokens = avl_alloc_tree(compare_reduce_nodes, free);
		
		struct avl_tree_t* subgrammars = avl_alloc_tree(compare_subgrammar_nodes, free_subgrammar_node);
		
		stateinfo_foreach(stateinfo, ({
			void runme(struct trie* trie, struct unsignedset* whitespace, struct unsignedset* tokens)
			{
				ENTER;
				
				if (trie->reduce_as)
				{
					unsignedset_foreach(tokens, ({
						void runme(unsigned token)
						{
							add_reduce(reduce_tokens, token, trie->reduce_as, trie->reductioninfo, trie->structinfo);
						}
						runme;
					}));
					
					unsignedset_update(all_tokens, whitespace);
					unsignedset_update(all_tokens, tokens);
				}
				
				for (unsigned i = 0, n = trie->transitions.n; i < n; i++)
				{
					const struct trie_transition* const ele = trie->transitions.data[i];
					
					add_shift(shift_tokens, ele->token, ele->to, whitespace, tokens);
					
					unsignedset_update(all_tokens, ele->whitespace);
					
					unsignedset_add(all_tokens, ele->token);
				}
				
				for (unsigned i = 0, n = trie->grammars.n; i < n; i++)
				{
					const struct trie_grammar_transition* ele = trie->grammars.data[i];
					
					dpvs(ele->grammar);
					
					add_subgrammar(subgrammars, ele->grammar, ele->to, whitespace, tokens);
				}
				
				EXIT;
			}
			runme;
		}));
		
		struct lex_state* tokenizer_start;
		
		// don't free 'tokens', lex will do that
		struct unsignedsetset* tokens = lex_build_tokenzer(
			/* (in/out) struct lex* lex:            */ lex,
			/* (   out) struct lex_state* start:    */ &tokenizer_start,
			/* (in)     struct unsignedset* tokens: */ all_tokens);
		
		state->tokenizer_start = tokenizer_start;
		
		unsignedsetset_foreach(tokens, ({
			void runme(struct unsignedset* ele)
			{
				ENTER;
				
				unsigned first = unsignedset_head(ele);
				
				dpv(first);
				
				// is this a shift or a reduce transition?
				if (avl_search(shift_tokens, &first))
				{
					struct stateinfo* subinfo = new_stateinfo();
					
					unsignedset_foreach(ele, ({
						void runme(unsigned token)
						{
							dpv(token);
							
							if (avl_search(reduce_tokens, &token))
							{
								// struct reduce_node* rn = rnode->item;
								TODO;
								exit(1);
							}
							
							struct shift_node* shift = avl_search(shift_tokens, &token)->item;
							
							stateinfo_foreach(shift->stateinfo, ({
								void runme(struct trie* subtrie, struct unsignedset* subwhitespace, struct unsignedset* subtokens) {
									struct unsignedset* dup1 = unsignedset_clone(subwhitespace);
									struct unsignedset* dup2 = unsignedset_clone(subtokens);
									stateinfo_add(subinfo, subtrie, dup1, dup2);
									free_unsignedset(dup1), free_unsignedset(dup2);
								}
								runme;
							}));
						}
						runme;
					}));
					
					expand_stateinfo(subinfo, named_tries, named_firsts);
					
					struct avl_node_t* node = avl_search(mappings, &subinfo);
					
					if (node)
					{
						struct mapping* submapping = node->item;
						
						yacc_state_add_transition(state, ele, submapping->state);
					}
					else
					{
						struct yacc_state* substate = new_yacc_state();
						
						struct mapping* submapping = new_mapping(subinfo, substate);
						
						yacc_state_add_transition(state, ele, substate);
						
						avl_insert(mappings, submapping);
						
						quack_append(todo, submapping);
					}
					
					free_stateinfo(subinfo);
				}
				else if (avl_search(reduce_tokens, &first))
				{
					struct string* reduce_as = NULL;
					struct reductioninfo* reductioninfo;
					struct structinfo* structinfo;
					
					unsignedset_foreach(ele, ({
						void runme(unsigned token) {
							dpv(token);
							
							if (avl_search(shift_tokens, &token))
							{
								TODO;
								// shift_reduce_error();
								exit(1);
							}
							
							struct avl_node_t* node = avl_search(reduce_tokens, &first);
							
							assert(node);
							
							struct reduce_node* reduce = node->item;
							
							dpvs(reduce->reduce_as);
							
							if (!reduce_as)
							{
								reduce_as = reduce->reduce_as;
								reductioninfo = reduce->reductioninfo;
								structinfo = reduce->structinfo;
							}
							else if (!strings_are_equal(reduce_as, reduce->reduce_as))
							{
								TODO;
							}
						}
						runme;
					}));
					
					yacc_state_add_reduce_transition(state, ele, reduce_as, reductioninfo, structinfo);
				}
				else
				{
					// huh?
					TODO;
				}
				
				EXIT;
			}
			runme;
		}));
		
		avl_tree_foreach(subgrammars, ({
			void runme(void* ptr)
			{
				struct subgrammar_node* const ele = ptr;
				
				dpvs(ele->grammar);
				
				struct stateinfo* subinfo = new_stateinfo();
				
				stateinfo_foreach(ele->stateinfo, ({
					void runme(struct trie* subtrie, struct unsignedset* subwhitespace, struct unsignedset* subtokens)
					{
						struct unsignedset* dup1 = unsignedset_clone(subwhitespace);
						struct unsignedset* dup2 = unsignedset_clone(subtokens);
						stateinfo_add(subinfo, subtrie, dup1, dup2);
						free_unsignedset(dup1), free_unsignedset(dup2);
					}
					runme;
				}));
				
				expand_stateinfo(subinfo, named_tries, named_firsts);
				
				struct avl_node_t* node = avl_search(mappings, &subinfo);
				
				if (node)
				{
					struct mapping* submapping = node->item;
					
					yacc_state_add_grammar_transition(state, ele->grammar, submapping->state);
				}
				else
				{
					struct yacc_state* substate = new_yacc_state();
					
					struct mapping* submapping = new_mapping(subinfo, substate);
					
					yacc_state_add_grammar_transition(state, ele->grammar, substate);
					
					avl_insert(mappings, submapping);
					
					quack_append(todo, submapping);
				}
				
				free_stateinfo(subinfo);
			}
			runme;
		}));
			
		#ifdef DOTOUT
		yacc_state_dotout(start);
		#endif
		
		#ifdef VERBOSE
		completed++;
		#endif
		
		free_unsignedset(all_tokens);
		
		free_unsignedsetset(tokens);
		
		avl_free_tree(shift_tokens);
		
		avl_free_tree(reduce_tokens);
		
		avl_free_tree(subgrammars);
	}
	
	#ifdef VERBOSE
	signal(SIGALRM, default_sighandler);
	#endif
	
	if (minimize_lexer)
	{
		lex_minimize_lexer(lex, start);
	}
	
	free_quack(todo);
	
	avl_free_tree(mappings);
	
	avl_free_tree(named_firsts);
	
	avl_free_tree(structinfos);
	
	avl_free_tree(named_tries);
	
	EXIT;
	return start;
}











