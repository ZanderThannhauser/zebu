
struct out_shared
{
	struct ystate_to_id* ytoi;
	struct lstate_to_id* ltoi;
	struct tokenset_to_id* ttoi;

	struct dyntable* shifts;
	struct dyntable* reduces;
	struct dyntable* lexer;

	struct dynvector* starts;
	struct dynvector* defaults;
	struct dynvector* accepts;
};
