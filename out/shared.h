
#if 0
struct out_shared
{
	struct ystate_to_id* ytoi;
	struct lstate_to_id* ltoi;
	struct tokenset_to_id* ttoi;
	
	// (parser state, token/grammar) -> new parser state
	struct dyntable* shifts;
	
	// (parser state, token) -> grammar
	struct dyntable* reduces;
	
	// (parser state, token) -> grammar
	struct dyntable* popcounts;
	
	// (tokenizer state, input char) -> new tokenizer state
	struct dyntable* lexer;
	
	// (parser state) -> (tokenizer start state)
	struct dynvector* starts;
	
	// (tokenizer state) -> default transition
	struct dynvector* defaults;
	
	// (tokenizer state) -> EOF transition
	struct dynvector* EOFs;
	
	// (tokenizer state) -> token
	struct dynvector* accepts;
};
#endif
