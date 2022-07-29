
#include <debug.h>

#include <misc/frame_counter.h>

#include <yacc/phase_counter.h>

#include <set/of_tokens/struct.h>
#include <set/of_tokens/compare.h>

#include <lex/phase_counter.h>

/*#include <set/of_tokens/to_string.h>*/

#include <lex/state/struct.h>
#include <lex/state/subdotout.h>

#include "struct.h"
#include "dotout.h"

#ifdef DEBUGGING

static void helper(FILE* out, struct yacc_state* state)
{
	ENTER;
	
	if (state->phase != yacc_phase_counter)
	{
		size_t i, n;
		
		state->phase = yacc_phase_counter;
		
		assert(state->tokenizer_start);
		
		lex_state_subdotout(out, state, state->tokenizer_start);
		
		// normal transitions:
		for (i = 0, n = state->transitions.n; i < n; i++)
		{
			struct ytransition* t = state->transitions.data[i];
			
			helper(out, t->to);
			
			void subhelper(struct lex_state* ls)
			{
				unsigned i, n;
				
				if (ls->phase != lex_phase_counter)
				{
					ls->phase = lex_phase_counter;
					
					if (ls->accepting && !compare_tokensets(t->value, ls->accepting))
					{
						fprintf(out, ""
							"\"%p-%p\" -> \"%p-%p\" [" "\n"
								"\t" "label = \"\"" "\n"
								"\t" "color = \"black:white:black\"" "\n"
							"]" "\n"
						"", state, ls, t->to, t->to->tokenizer_start);
					}
					
					// normal transitions:
					for (i = 0, n = ls->transitions.n; i < n; i++)
					{
						struct ltransition* transition = ls->transitions.data[i];
						subhelper(transition->to);
					}
					
					// default transition?:
					if (ls->default_transition_to)
					{
						TODO;
					}
				}
			}
			
			if (t->value->n == 1 && t->value->data[0] == 0)
			{
				TODO;
			}
			else
			{
				lex_phase_counter++, subhelper(state->tokenizer_start);
			}
		}
		
		// reduction transitions:
		for (i = 0, n = state->reduction_transitions.n; i < n; i++)
		{
			struct rytransition* t = state->reduction_transitions.data[i];
			
			fprintf(out, ""
				"\"%p-%p\" [" "\n"
					"\t" "shape = box;" "\n"
					"\t" "label = \"%s\";" "\n"
				"]" "\n"
			"", state, t->reduce_as, t->reduce_as);
			
			void subhelper(struct lex_state* ls)
			{
				unsigned i, n;
				
				if (ls->phase != lex_phase_counter)
				{
					ls->phase = lex_phase_counter;
					
					if (ls->accepting && !compare_tokensets(t->value, ls->accepting))
					{
						fprintf(out, ""
							"\"%p-%p\" -> \"%p-%p\" [" "\n"
								"\t" "label = \"\"" "\n"
								"\t" "style = \"dashed\"" "\n"
							"]" "\n"
						"", state, ls, state, t->reduce_as);
					}
					
					// normal transitions:
					for (i = 0, n = ls->transitions.n; i < n; i++)
					{
						struct ltransition* transition = ls->transitions.data[i];
						subhelper(transition->to);
					}
					
					// default transition?:
					if (ls->default_transition_to)
					{
						TODO;
					}
				}
			}
			
			if (t->value->n == 1 && t->value->data[0] == 0)
			{
				fprintf(out, ""
					"\"%p-%p\" -> \"%p-%p\" [" "\n"
						"\t" "label = \"<EOF>\"" "\n"
						"\t" "style = \"dashed\"" "\n"
					"]" "\n"
				"", state, state->tokenizer_start, state, t->reduce_as);
			}
			else
			{
				lex_phase_counter++, subhelper(state->tokenizer_start);
			}
		}
		
		// grammar transitions:
		for (i = 0, n = state->grammar_transitions.n; i < n; i++)
		{
			struct gytransition* t = state->grammar_transitions.data[i];
			
			helper(out, t->to);
			
			fprintf(out, ""
				"\"%p-%p\" -> \"%p-%p\" [" "\n"
					"\t" "label = \"%s\"" "\n"
				"]" "\n"
			"", state, state->tokenizer_start, t->to, t->to->tokenizer_start, t->grammar);
			
		}
	}
	
	EXIT;
}

void yacc_state_dotout(struct yacc_state* state)
{
	ENTER;
	
	char path[PATH_MAX];
	
	snprintf(path, PATH_MAX, "dot/%u.dot", frame_counter++);
	
	dpvs(path);
	
	FILE* out = fopen(path, "w");
	
	if (!out)
	{
		fprintf(stderr, "%s: fopen(\"%s\"): %m\n", argv0, path);
		abort();
	}
	
	fprintf(out, "digraph {" "\n");
	
	fprintf(out, "\t" "rankdir = LR;" "\n");
	
	fprintf(out, "\"%p-%p\" [ style = bold; ];" "\n", state, state->tokenizer_start);
	
	yacc_phase_counter++;
	
	helper(out, state);
	
	fprintf(out, "}" "\n");
	
	if (out)
		fclose(out);
	
	EXIT;
}

#endif
