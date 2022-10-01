
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* const* argv)
{
	int opt;
	
	const char* argv0 = argv[0];
	
	const char* source_path = NULL;
	const char* varname = NULL;
	
	while ((opt = getopt(argc, argv, "o:v:")) != -1)
	{
		switch (opt)
		{
			case 'o': source_path = optarg; break;
			
			case 'v': varname = optarg; break;
			
			default: goto bad_args;
		}
	}
	
	const char* input_path = argv[optind++];
	
	if (!input_path || !source_path || !varname)
		goto bad_args;
	
	char header_path[PATH_MAX];
	
	{
		strcpy(header_path, source_path);
		
		char* dot = rindex(header_path, '.');
		
		if (!dot || strcmp(dot, ".c")) goto bad_args;
		
		dot[1] = 'h';
	}
	
	FILE* input = fopen(input_path, "r");
	
	if (!input)
	{
		fprintf(stderr, "%s: fopen(\"%s\"): %m\n", argv0, input_path);
		return 1;
	}
	
	FILE* source = fopen(source_path, "w");
	
	if (!source)
	{
		fprintf(stderr, "%s: fopen(\"%s\"): %m\n", argv0, source_path);
		return 1;
	}
	
	FILE* header = fopen(header_path, "w");
	
	if (!header)
	{
		fprintf(stderr, "%s: fopen(\"%s\"): %m\n", argv0, header_path);
		return 1;
	}
	
	fprintf(header, "extern const char* %s;", varname);
	fprintf(source, "const char* %s = \"\"\n", varname);
	
	fprintf(source, "\t\"");
	int c;
	while ((c = getc(input)) != EOF)
	{
		switch (c)
		{
			case '\n':
				fprintf(source, "\" \"\\n\"\n\t\"");
				break;
			case '\t':
				fprintf(source, "\\t");
				break;
			case '\"':
				fprintf(source, "\\\"");
				break;
			case '\'':
				fprintf(source, "\\\'");
				break;
			case '\\':
				fprintf(source, "\\\\");
				break;
			case ' ':
			case '!':
			case '@':
			case '#':
			case '$':
			case '%':
			case '^':
			case '&':
			case '*':
			case '(':
			case ')':
			case '-':
			case '`':
			case '+':
			case '_':
			case '=':
			case '~':
			case '[': case ']':
			case '{': case '}':
			case ':': case ';':
			case ',': case '.':
			case '|':
			case '<': case '>':
			case '?': case '/':
			case '0' ... '9':
			case 'a' ... 'z':
			case 'A' ... 'Z':
				putc(c, source);
				break;
			default:
				printf("c == %c\n", c);
				assert(!"TODO");
				break;
		}
	}
	
	fprintf(source, "\";\n");
	
	fclose(input);
	fclose(source);
	fclose(header);
	
	return 0;
	
	bad_args:
	fprintf(stderr, "usage: %s input/path -o output/path.c\n", argv0);
	return 1;
}
















