
#ifdef DEBUGGING

#include <debug.h>

__thread int debug_depth = 0;

static void escape(char str[5], unsigned char ch)
{
	switch (ch)
	{
		case ' ':
		case '`': case '~':
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
		case '=': case '+':
		case '[': case '{':
		case ']': case '}':
		          case '|':
		case ';': case ':':
		case ',': case '<':
		case '.': case '>':
		case '/': case '?':
		case 'A' ... 'Z':
		case 'a' ... 'z':
			str[0] = ch;
			str[1] = '\0';
			break;
		
		case '\n': strcpy(str, "\\n"); break;
		case '\t': strcpy(str, "\\t"); break;
		case '\\': strcpy(str, "\\\\"); break;
		case '\"': strcpy(str, "\\\""); break;
		case '\'': strcpy(str, "\\\'"); break;
		
		default:
			sprintf(str, "\\%#o", ch);
			break;
	}
}

void real_dpvc(const char* e, char ch)
{
	char str[5] = {};
	
	escape(str, ch);
	
	printf("%*s%s == '%s'\n", debug_depth, "", e, str);
}


void real_dpvsn(const char* e, const char* s, size_t n)
{
	char str[5] = {};
	
	printf("%*s%s == \"", debug_depth, "", e);
	if (!s)
		s = "(null)";
	while (n-- && *s)
	{
		escape(str, *s++);
		fputs(str, stdout);
	}
	printf("\"\n");
}

void real_dpvwsn(const char* e, const wchar_t* s, size_t n)
{
	TODO;
}





#endif



























