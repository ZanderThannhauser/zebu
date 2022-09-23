
#include <assert.h>
#include <errno.h>
#include <stdio.h>

#include "argv0.h"
#include "value.h"
#include "parser.h"
#include "evaluate.h"
#include "scope.h"
#include "print.h"

static void usage()
{
	printf("usage: %s <input/file.lisp>\n", argv0);
}

int main(int argc, const char** argv)
{
	if (argc < 2)
	{
		usage();
		return 1;
	}
	
	const char* input_path = argv[1];
	
	FILE* stream = fopen(input_path, "r");
	
	if (!stream)
	{
		fprintf(stderr, "%s: fopen(\"%s\"): %m\n", argv0, input_path);
		return 2;
	}
	
	struct zebu_$start* start = zebu_parse(stream);
	
	struct scope* scope = new_scope(NULL);
	
	scope_define_builtins(scope);
	
	for (unsigned i = 0, n = start->roots->values.n; i < n; i++)
	{
		struct zebu_value* ptree = start->roots->values.data[i];
		
		struct value* before = new_value_from_ptree(ptree);
		
		struct value* after = evaluate(scope, before);
		
		print(after);
		
		free_value(before);
		free_value(after);
	}
	
	free_scope(scope);
	
	free_zebu_$start(start);
	
	fclose(stream);
	
	return 0;
}

















