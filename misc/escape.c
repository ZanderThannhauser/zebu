
#ifdef DOTOUT

#include <stdio.h>

#include <debug.h>

#include "escape.h"

void escape(char* out, unsigned char value)
{
	switch (value)
	{
		case 'a' ... 'z':
		case 'A' ... 'Z':
		case '~': case '`':
		case '1': case '!':
		case '2': case '@':
		case '3': case '#':
		case '4': case '$':
		case '5': case '%':
		case '6': case '^':
		case '7': case '&':
		case '8': case '*':
		case '9': case '(':
		case '0': case ')':
		case '-': case '_':
		case '+': case '=':
		case '[': case '{':
		case ']': case '}':
		case ';': case '|':
		case ',': case ':':
		case '.': case '<':
		case '/': case '>':
		case ' ':
		case '?':
			sprintf(out, "'%c'", value);
			break;
		
		case '\\':
			sprintf(out, "'\\\\\\\\'");
			break;
		
		case '\t':
			sprintf(out, "'\\\\t'");
			break;
		
		case '\n':
			sprintf(out, "'\\\\n'");
			break;
		
		case '\"':
			sprintf(out, "'\\\\\\\"'");
			break;
		
		case '\'':
			sprintf(out, "'\\\\\\\''");
			break;
		
		default:
			sprintf(out, "'\\\\x%02hhX'", value);
			break;
	}
}

#endif















