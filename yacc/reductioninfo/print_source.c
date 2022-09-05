
#include <debug.h>

#include <set/string/foreach.h>
#include <set/string/is_empty.h>

#include "struct.h"
#include "print_source.h"

void reductioninfo_print_source(
	struct reductioninfo* this,
	FILE* stream)
{
	ENTER;
	
	assert(this);
	
	bool once = true;
	
	stringset_foreach(this->tags, ({
		void runme(struct string* tag)
		{
			if (once)
			{
				fprintf(stream, ""
					"\t" "\t" "value->%s = data.data[--yacc.n, --data.n];" "\n"
				"", tag->chars);
				once = false;
			}
			else
			{
				fprintf(stream, ""
					"\t" "\t" "value->%s = inc_%s(data.data[data.n]);" "\n"
				"", tag->chars, tag->chars);
			}
		}
		runme;
	}));
	
	if (stringset_is_empty(this->tags))
	{
		fprintf(stream, ""
			"\t" "\t" "free_%s(data.data[--yacc.n, --data.n]);" "\n"
		"", this->grammar ? this->grammar->chars : "token");
	}
	
	if (this->prev)
	{
		reductioninfo_print_source(this->prev, stream);
	}
	
	EXIT;
}












