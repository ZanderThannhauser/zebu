
struct out_shared
{
	struct ystate_to_id* ytoi;
	struct lstate_to_id* ltoi;
	struct tokenset_to_id* ttoi;
	
	// (parser state, token/grammar) -> new parser state
	struct dyntable* shifts;
	
	// (parser state, token) -> grammar
	struct dyntable* reduces;
	
	// (tokenizer state, input char) -> new tokenizer state
	struct dyntable* lexer;
	
	// (grammar, token/grammar) -> is the given token in the grammar's "firsts" set?
	struct dyntable* firsts;
	
	// (parser state) -> (tokenizer start state)
	struct dynvector* starts;
	
	// (tokenizer state) -> default transition
	struct dynvector* defaults;
	
	// (tokenizer state) -> EOF transition
	struct dynvector* EOFs;
	
	// (tokenizer state) -> token
	struct dynvector* accepts;
};
