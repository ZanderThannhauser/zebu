
#include <assert.h>

#include <debug.h>

#include <string/struct.h>

#include <cmdln/parser_program_name.h>

#include <misc/format_flags/struct.h>

#include <yacc/structinfo/struct.h>
#include <yacc/structinfo/foreach.h>
#include <yacc/structinfo/node.h>

#include "struct.h"
#include "print_source.h"

void reductioninfo_print_source(
	struct reductioninfo* this,
	struct structinfo* structinfo,
	const char* grammar,
	const char* prefix,
	FILE* stream)
{
	ENTER;
	
	switch (this->kind)
	{
		case rik_token:
		{
			fprintf(stream, ""
				"{" "\n"
					"struct %s_token* token = data.data[--yacc.n, --data.n];" "\n"
					"if (token->line < value->startline) value->startline = token->line;" "\n"
					"if (value->endline < token->line) value->endline = token->line;" "\n"
			"", prefix);
			
			structinfo_foreach(this->structinfo, ({
				void runme(struct structinfo_node* node)
				{
					const char* name = node->name->chars;
					
					switch (node->type)
					{
						case snt_token_scalar:
						{
							fprintf(stream, ""
								"free_%s_token(value->%s), value->%s = inc_%s_token(token);" "\n"
							"", prefix, name, name, prefix);
							break;
						}
						
						case snt_token_array:
						{
							fprintf(stream, ""
								"if (value->%s.n == value->%s.cap)" "\n"
								"{" "\n"
									"value->%s.cap = value->%s.cap << 1 ?: 1;" "\n"
									"value->%s.data = realloc(value->%s.data, sizeof(*value->%s.data) * value->%s.cap);" "\n"
								"}" "\n"
								"memmove(value->%s.data + 1, value->%s.data, sizeof(*value->%s.data) * value->%s.n);" "\n"
								"value->%s.data[0] = inc_%s_token(token), value->%s.n++;" "\n"
							"", name, name,
							name, name,
							name, name, name, name,
							name, name, name, name,
							name, prefix, name);
							break;
						}
						
						case snt_scanf_scalar:
						{
							struct format_flags* fflags = node->scanf.fflags;
							
							dpvs(fflags->length_modifier_text);
							dpvc(fflags->conversion);
							dpvs(fflags->ctype);
							
							switch (fflags->conversion)
							{
								case 'i':
								{
									switch (fflags->length_modifier)
									{
										case lm_char:
										{
											fprintf(stream, ""
												"{" "\n"
													"char* m;" "\n"
													"errno = 0;" "\n"
													"signed long raw = strtol((char*) token->data, &m, 0);" "\n"
													"if (*m) {" "\n"
														"fprintf(stderr, \"%%s: strtol('%%s'): invalid character '%%c'!\\n\", %s, token->data, *m);" "\n"
														"exit(1);" "\n"
													"} else if (errno) {" "\n"
														"fprintf(stderr, \"%%s: strtol('%%s'): %%m!\\n\", %s, token->data);" "\n"
														"exit(1);" "\n"
													"} else if (raw >= SCHAR_MAX) {" "\n"
														"fprintf(stderr, \"%%s: %%%%i scanf-token given a value too high for an signed int!\\n\", %s);" "\n"
														"exit(1);" "\n"
													"}" "\n"
													"value->%s = raw;" "\n"
												"}" "\n"
											"", parser_program_name, parser_program_name, parser_program_name, name);
											break;
										}
										
										case lm_short:
										{
											fprintf(stream, ""
												"{" "\n"
													"char* m;" "\n"
													"errno = 0;" "\n"
													"signed long raw = strtol((void*) token->data, &m, 0);" "\n"
													"if (*m) {" "\n"
														"fprintf(stderr, \"%%s: strtol('%%s'): invalid character '%%c'!\\n\", %s, token->data, *m);" "\n"
														"exit(1);" "\n"
													"} else if (errno) {" "\n"
														"fprintf(stderr, \"%%s: strtol('%%s'): %%m!\\n\", %s, token->data);" "\n"
														"exit(1);" "\n"
													"} else if (raw >= SHRT_MAX) {" "\n"
														"fprintf(stderr, \"%%s: %%%%i scanf-token given a value too high for an signed int!\\n\", %s);" "\n"
														"exit(1);" "\n"
													"}" "\n"
													"value->%s = raw;" "\n"
												"}" "\n"
											"", parser_program_name, parser_program_name, parser_program_name, name);
											break;
										}
										
										case lm_int:
										{
											fprintf(stream, ""
												"{" "\n"
													"char* m;" "\n"
													"errno = 0;" "\n"
													"signed long raw = strtol((char*) token->data, &m, 0);" "\n"
													"if (*m) {" "\n"
														"fprintf(stderr, \"%%s: strtol('%%s'): invalid character '%%c'!\\n\", %s, token->data, *m);" "\n"
														"exit(1);" "\n"
													"} else if (errno) {" "\n"
														"fprintf(stderr, \"%%s: strtol('%%s'): %%m!\\n\", %s, token->data);" "\n"
														"exit(1);" "\n"
													"} else if (raw >= INT_MAX) {" "\n"
														"fprintf(stderr, \"%%s: %%%%i scanf-token given a value too high for an signed int!\\n\", %s);" "\n"
														"exit(1);" "\n"
													"}" "\n"
													"value->%s = raw;" "\n"
												"}" "\n"
											"", parser_program_name, parser_program_name, parser_program_name, name);
											break;
										}
										
										case lm_long:
										{
											fprintf(stream, ""
												"{" "\n"
													"char* m;" "\n"
													"errno = 0;" "\n"
													"signed long raw = strtol((char*) token->data, &m, 0);" "\n"
													"if (*m) {" "\n"
														"fprintf(stderr, \"%%s: strtol('%%s'): invalid character '%%c'!\\n\", %s, token->data, *m);" "\n"
														"exit(1);" "\n"
													"} else if (errno) {" "\n"
														"fprintf(stderr, \"%%s: strtol('%%s'): %%m!\\n\", %s, token->data);" "\n"
														"exit(1);" "\n"
													"}" "\n"
													"value->%s = raw;" "\n"
												"}" "\n"
											"", parser_program_name, parser_program_name, name);
											break;
										}
										
										case lm_long_long:
										{
											fprintf(stream, ""
												"{" "\n"
													"char* m;" "\n"
													"errno = 0;" "\n"
													"signed long long raw = strtoll((char*) token->data, &m, 0);" "\n"
													"if (*m) {" "\n"
														"fprintf(stderr, \"%%s: strtoll('%%s'): invalid character '%%c'!\\n\", %s, token->data, *m);" "\n"
														"exit(1);" "\n"
													"} else if (errno) {" "\n"
														"fprintf(stderr, \"%%s: strtoll('%%s'): %%m!\\n\", %s, token->data);" "\n"
														"exit(1);" "\n"
													"}" "\n"
													"value->%s = raw;" "\n"
												"}" "\n"
											"", parser_program_name, parser_program_name, name);
											break;
										}
										
										default: TODO; break;
									}
								}
								break;
								
								case 'd': TODO; break;
								
								case 'u':
								{
									switch (fflags->length_modifier)
									{
										case lm_char:
										{
											fprintf(stream, ""
												"{" "\n"
													"char *m;" "\n"
													"errno = 0;" "\n"
													"unsigned long raw = strtoul((char*) token->data, &m, 10);" "\n"
													"if (*m) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): invalid character '%%c'!\\n\", %s, token->data, *m);" "\n"
														"exit(1);" "\n"
													"} else if (errno) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): %%m!\\n\", %s, token->data);" "\n"
														"exit(1);" "\n"
													"} else if (raw >= UCHAR_MAX) {" "\n"
														"fprintf(stderr, \"%%s: %%%%o scanf-token given a value too high for an unsigned char!\\n\", %s);" "\n"
														"exit(1);" "\n"
													"}" "\n"
													"value->%s = raw;" "\n"
												"}" "\n"
											"", parser_program_name, parser_program_name, parser_program_name, name);
											break;
										}
										
										case lm_short:
										{
											fprintf(stream, ""
												"{" "\n"
													"char *m;" "\n"
													"errno = 0;" "\n"
													"unsigned long raw = strtoul((char*) token->data, &m, 10);" "\n"
													"if (*m) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): invalid character '%%c'!\\n\", %s, token->data, *m);" "\n"
														"exit(1);" "\n"
													"} else if (errno) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): %%m!\\n\", %s, token->data);" "\n"
														"exit(1);" "\n"
													"} else if (raw >= USHRT_MAX) {" "\n"
														"fprintf(stderr, \"%%s: %%%%o scanf-token given a value too high for an unsigned short!\\n\", %s);" "\n"
														"exit(1);" "\n"
													"}" "\n"
													"value->%s = raw;" "\n"
												"}" "\n"
											"", parser_program_name, parser_program_name, parser_program_name, name);
											break;
										}
										
										case lm_int:
										{
											fprintf(stream, ""
												"{" "\n"
													"char *m;" "\n"
													"errno = 0;" "\n"
													"unsigned long raw = strtoul((char*) token->data, &m, 10);" "\n"
													"if (*m) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): invalid character '%%c'!\\n\", %s, token->data, *m);" "\n"
														"exit(1);" "\n"
													"} else if (errno) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): %%m!\\n\", %s, token->data);" "\n"
														"exit(1);" "\n"
													"} else if (raw >= UINT_MAX) {" "\n"
														"fprintf(stderr, \"%%s: %%%%o scanf-token given a value too high for an unsigned int!\\n\", %s);" "\n"
														"exit(1);" "\n"
													"}" "\n"
													"value->%s = raw;" "\n"
												"}" "\n"
											"", parser_program_name, parser_program_name, parser_program_name, name);
											break;
										}
										
										case lm_long:
										{
											fprintf(stream, ""
												"{" "\n"
													"char *m;" "\n"
													"errno = 0;" "\n"
													"unsigned long raw = strtoul((char*) token->data, &m, 10);" "\n"
													"if (*m) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): invalid character '%%c'!\\n\", %s, token->data, *m);" "\n"
														"exit(1);" "\n"
													"} else if (errno) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): %%m!\\n\", %s, token->data);" "\n"
														"exit(1);" "\n"
													"}" "\n"
													"value->%s = raw;" "\n"
												"}" "\n"
											"", parser_program_name, parser_program_name, name);
											break;
										}
										
										case lm_long_long:
										{
											fprintf(stream, ""
												"{" "\n"
													"char *m;" "\n"
													"errno = 0;" "\n"
													"unsigned long long raw = strtoull((char*) token->data, &m, 10);" "\n"
													"if (*m) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): invalid character '%%c'!\\n\", %s, token->data, *m);" "\n"
														"exit(1);" "\n"
													"} else if (errno) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): %%m!\\n\", %s, token->data);" "\n"
														"exit(1);" "\n"
													"}" "\n"
													"value->%s = raw;" "\n"
												"}" "\n"
											"", parser_program_name, parser_program_name, name);
											break;
										}
										
										default: TODO; break;
									}
									break;
								}
								
								case 'o':
								{
									switch (fflags->length_modifier)
									{
										case lm_char:
										{
											fprintf(stream, ""
												"{" "\n"
													"char *m;" "\n"
													"errno = 0;" "\n"
													"unsigned long raw = strtoul((char*) token->data, &m, 8);" "\n"
													"if (*m) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): invalid character '%%c'!\\n\", %s, token->data, *m);" "\n"
														"exit(1);" "\n"
													"} else if (errno) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): %%m!\\n\", %s, token->data);" "\n"
														"exit(1);" "\n"
													"} else if (raw >= UCHAR_MAX) {" "\n"
														"fprintf(stderr, \"%%s: %%%%o scanf-token given a value too high for an unsigned char!\\n\", %s);" "\n"
														"exit(1);" "\n"
													"}" "\n"
													"value->%s = raw;" "\n"
												"}" "\n"
											"", parser_program_name, parser_program_name, parser_program_name, name);
											break;
										}
										
										case lm_short:
										{
											fprintf(stream, ""
												"{" "\n"
													"char *m;" "\n"
													"errno = 0;" "\n"
													"unsigned long raw = strtoul((char*) token->data, &m, 8);" "\n"
													"if (*m) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): invalid character '%%c'!\\n\", %s, token->data, *m);" "\n"
														"exit(1);" "\n"
													"} else if (errno) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): %%m!\\n\", %s, token->data);" "\n"
														"exit(1);" "\n"
													"} else if (raw >= USHRT_MAX) {" "\n"
														"fprintf(stderr, \"%%s: %%%%o scanf-token given a value too high for an unsigned short!\\n\", %s);" "\n"
														"exit(1);" "\n"
													"}" "\n"
													"value->%s = raw;" "\n"
												"}" "\n"
											"", parser_program_name, parser_program_name, parser_program_name, name);
											break;
										}
										
										case lm_int:
										{
											fprintf(stream, ""
												"{" "\n"
													"char *m;" "\n"
													"errno = 0;" "\n"
													"unsigned long raw = strtoul((char*) token->data, &m, 8);" "\n"
													"if (*m) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): invalid character '%%c'!\\n\", %s, token->data, *m);" "\n"
														"exit(1);" "\n"
													"} else if (errno) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): %%m!\\n\", %s, token->data);" "\n"
														"exit(1);" "\n"
													"} else if (raw >= UINT_MAX) {" "\n"
														"fprintf(stderr, \"%%s: %%%%o scanf-token given a value too high for an unsigned int!\\n\", %s);" "\n"
														"exit(1);" "\n"
													"}" "\n"
													"value->%s = raw;" "\n"
												"}" "\n"
											"", parser_program_name, parser_program_name, parser_program_name, name);
											break;
										}
										
										case lm_long:
										{
											fprintf(stream, ""
												"{" "\n"
													"char *m;" "\n"
													"errno = 0;" "\n"
													"unsigned long raw = strtoul((char*) token->data, &m, 8);" "\n"
													"if (*m) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): invalid character '%%c'!\\n\", %s, token->data, *m);" "\n"
														"exit(1);" "\n"
													"} else if (errno) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): %%m!\\n\", %s, token->data);" "\n"
														"exit(1);" "\n"
													"}" "\n"
													"value->%s = raw;" "\n"
												"}" "\n"
											"", parser_program_name, parser_program_name, name);
											break;
										}
										
										case lm_long_long:
										{
											fprintf(stream, ""
												"{" "\n"
													"char *m;" "\n"
													"errno = 0;" "\n"
													"unsigned long long raw = strtoull((char*) token->data, &m, 8);" "\n"
													"if (*m) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): invalid character '%%c'!\\n\", %s, token->data, *m);" "\n"
														"exit(1);" "\n"
													"} else if (errno) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): %%m!\\n\", %s, token->data);" "\n"
														"exit(1);" "\n"
													"}" "\n"
													"value->%s = raw;" "\n"
												"}" "\n"
											"", parser_program_name, parser_program_name, name);
											break;
										}
										
										default: TODO; break;
									}
									break;
								}
								
								case 'x':
								case 'X':
								{
									switch (fflags->length_modifier)
									{
										case lm_char:
										{
											fprintf(stream, ""
												"{" "\n"
													"char *m;" "\n"
													"errno = 0;" "\n"
													"unsigned long raw = strtoul((char*) token->data, &m, 16);" "\n"
													"if (*m) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): invalid character '%%c'!\\n\", %s, token->data, *m);" "\n"
														"exit(1);" "\n"
													"} else if (errno) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): %%m!\\n\", %s, token->data);" "\n"
														"exit(1);" "\n"
													"} else if (raw >= UCHAR_MAX) {" "\n"
														"fprintf(stderr, \"%%s: %%%%o scanf-token given a value too high for an unsigned char!\\n\", %s);" "\n"
														"exit(1);" "\n"
													"}" "\n"
													"value->%s = raw;" "\n"
												"}" "\n"
											"", parser_program_name, parser_program_name, parser_program_name, name);
											break;
										}
										
										case lm_short:
										{
											fprintf(stream, ""
												"{" "\n"
													"char *m;" "\n"
													"errno = 0;" "\n"
													"unsigned long raw = strtoul((char*) token->data, &m, 16);" "\n"
													"if (*m) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): invalid character '%%c'!\\n\", %s, token->data, *m);" "\n"
														"exit(1);" "\n"
													"} else if (errno) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): %%m!\\n\", %s, token->data);" "\n"
														"exit(1);" "\n"
													"} else if (raw >= USHRT_MAX) {" "\n"
														"fprintf(stderr, \"%%s: %%%%o scanf-token given a value too high for an unsigned short!\\n\", %s);" "\n"
														"exit(1);" "\n"
													"}" "\n"
													"value->%s = raw;" "\n"
												"}" "\n"
											"", parser_program_name, parser_program_name, parser_program_name, name);
											break;
										}
										
										case lm_int:
										{
											fprintf(stream, ""
												"{" "\n"
													"char *m;" "\n"
													"errno = 0;" "\n"
													"unsigned long raw = strtoul((char*) token->data, &m, 16);" "\n"
													"if (*m) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): invalid character '%%c'!\\n\", %s, token->data, *m);" "\n"
														"exit(1);" "\n"
													"} else if (errno) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): %%m!\\n\", %s, token->data);" "\n"
														"exit(1);" "\n"
													"} else if (raw >= UINT_MAX) {" "\n"
														"fprintf(stderr, \"%%s: %%%%o scanf-token given a value too high for an unsigned int!\\n\", %s);" "\n"
														"exit(1);" "\n"
													"}" "\n"
													"value->%s = raw;" "\n"
												"}" "\n"
											"", parser_program_name, parser_program_name, parser_program_name, name);
											break;
										}
										
										case lm_long:
										{
											fprintf(stream, ""
												"{" "\n"
													"char *m;" "\n"
													"errno = 0;" "\n"
													"unsigned long raw = strtoul((char*) token->data, &m, 16);" "\n"
													"if (*m) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): invalid character '%%c'!\\n\", %s, token->data, *m);" "\n"
														"exit(1);" "\n"
													"} else if (errno) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): %%m!\\n\", %s, token->data);" "\n"
														"exit(1);" "\n"
													"}" "\n"
													"value->%s = raw;" "\n"
												"}" "\n"
											"", parser_program_name, parser_program_name, name);
											break;
										}
										
										case lm_long_long:
										{
											fprintf(stream, ""
												"{" "\n"
													"char *m;" "\n"
													"errno = 0;" "\n"
													"unsigned long long raw = strtoull((char*) token->data, &m, 16);" "\n"
													"if (*m) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): invalid character '%%c'!\\n\", %s, token->data, *m);" "\n"
														"exit(1);" "\n"
													"} else if (errno) {" "\n"
														"fprintf(stderr, \"%%s: strtoul('%%s'): %%m!\\n\", %s, token->data);" "\n"
														"exit(1);" "\n"
													"}" "\n"
													"value->%s = raw;" "\n"
												"}" "\n"
											"", parser_program_name, parser_program_name, name);
											break;
										}
										
										default: TODO; break;
									}
									break;
								}
								
								case 's':
								{
									switch (fflags->length_modifier)
									{
										case lm_int:
										{
											fprintf(stream, ""
												"value->%s = strdup((char*) token->data);" "\n"
											"", name);
											break;
										}
										
										case lm_long:
										{
											fprintf(stream, ""
												"{" "\n"
													"size_t len = mbstowcs(NULL, (void*) token->data, -1);" "\n"
													"if (!token->len) {" "\n"
														"fprintf(stderr, \"%%s: '%%%%ls' scanf-token given empty string!\\n\", %s);" "\n"
														"exit(1);" "\n"
													"} else if (len == (size_t) -1) {" "\n"
														"fprintf(stderr, \"%%s: error processing '%%%%ls' scanf-token: mbstowcs(): %%m \\n\", %s);" "\n"
														"exit(1);" "\n"
													"}" "\n"
													"mbstowcs(value->%s = malloc((len + 1) * sizeof(wchar_t)), (void*) token->data, len + 1);" "\n"
												"}" "\n"
											"", parser_program_name, parser_program_name, name);
											break;
										}
										
										default: TODO; break;
									}
									break;
								}
								
								case 'c':
								{
									switch (fflags->length_modifier)
									{
										case lm_int:
										{
											fprintf(stream, ""
												"{" "\n"
													"if (!token->len) {" "\n"
														"fprintf(stderr, \"%%s: '%%%%c' scanf-token given empty string!\\n\", %s);" "\n"
														"exit(1);" "\n"
													"}" "\n"
													"value->%s = token->data[0];" "\n"
												"}" "\n"
											"", parser_program_name, name);
											break;
										}
										
										case lm_long:
										{
											fprintf(stream, ""
												"if (!token->len) {" "\n"
													"fprintf(stderr, \"%%s: '%%%%lc' scanf-token given empty string!\\n\", %s);" "\n"
													"exit(1);" "\n"
												"} else if (mbstowcs(&value->%s, (void*) token->data, 1) == (size_t) -1) {" "\n"
													"fprintf(stderr, \"%%s: error processing '%%%%lc' scanf-token: mbstowcs(): %%m \\n\", %s);" "\n"
													"exit(1);" "\n"
												"}" "\n"
											"", parser_program_name, name, parser_program_name);
											break;
										}
										
										default: TODO; break;
									}
									break;
								}
								
								case 'f':
								case 'F':
								case 'e':
								case 'E':
								case 'g':
								case 'G':
								{
									switch (fflags->length_modifier)
									{
										case lm_int:
										{
											fprintf(stream, ""
												"{" "\n"
													"char *m;" "\n"
													"errno = 0, value->%s = strtof((char*) token->data, &m);" "\n"
													"if (*m) {" "\n"
														"fprintf(stderr, \"%%s: strtof('%%s'): invalid character '%%c'!\\n\", %s, token->data, *m);" "\n"
														"exit(1);" "\n"
													"} else if (errno) {" "\n"
														"fprintf(stderr, \"%%s: strtof('%%s'): %%m!\\n\", %s, token->data);" "\n"
														"exit(1);" "\n"
													"}" "\n"
												"}" "\n"
											"", name, parser_program_name, parser_program_name);
											break;
										}
										case lm_long:
										{
											fprintf(stream, ""
												"{" "\n"
													"char *m;" "\n"
													"errno = 0, value->%s = strtod((char*) token->data, &m);" "\n"
													"if (*m) {" "\n"
														"fprintf(stderr, \"%%s: strtod('%%s'): invalid character '%%c'!\\n\", %s, token->data, *m);" "\n"
														"exit(1);" "\n"
													"} else if (errno) {" "\n"
														"fprintf(stderr, \"%%s: strtod('%%s'): %%m!\\n\", %s, token->data);" "\n"
														"exit(1);" "\n"
													"}" "\n"
												"}" "\n"
											"", name, parser_program_name, parser_program_name);
											break;
										}
										case lm_long_double:
										{
											fprintf(stream, ""
												"{" "\n"
													"char *m;" "\n"
													"errno = 0, value->%s = strtold((char*) token->data, &m);" "\n"
													"if (*m) {" "\n"
														"fprintf(stderr, \"%%s: strtold('%%s'): invalid character '%%c'!\\n\", %s, token->data, *m);" "\n"
														"exit(1);" "\n"
													"} else if (errno) {" "\n"
														"fprintf(stderr, \"%%s: strtold('%%s'): %%m!\\n\", %s, token->data);" "\n"
														"exit(1);" "\n"
													"}" "\n"
												"}" "\n"
											"", name, parser_program_name, parser_program_name);
											break;
										}
										default: TODO; break;
									}
									break;
								}
								
								default:
									TODO;
									break;
							}
							
							break;
						}
						
						case snt_scanf_array:
						{
							TODO;
							break;
						}
						
						default:
							TODO;
							break;
					}
				}
				runme;
			}));
			
			fprintf(stream, ""
				"free_%s_token(token);" "\n"
				"}" "\n"
			"", prefix);
			break;
		}
		
		case rik_grammar:
		{
			const char* type = this->grammar->chars;
			
			fprintf(stream, ""
				"{" "\n"
				"struct %s_%s* subgrammar = data.data[--yacc.n, --data.n];" "\n"
				"if (subgrammar->startline < value->startline) value->startline = subgrammar->startline;" "\n"
				"if (value->endline < subgrammar->endline) value->endline = subgrammar->endline;" "\n"
			"", prefix, type);
			
			structinfo_foreach(this->structinfo, ({
				void runme(struct structinfo_node* node)
				{
					const char* name = node->name->chars;
					
					switch (node->type)
					{
						case snt_grammar_scalar:
						{
							fprintf(stream, ""
								"free_%s_%s(value->%s), value->%s = inc_%s_%s(subgrammar);" "\n"
							"", prefix, type, name, name, prefix, type);
							break;
						}
						
						case snt_grammar_array:
						{
							fprintf(stream, ""
								"if (value->%s.n == value->%s.cap)" "\n"
								"{" "\n"
									"value->%s.cap = value->%s.cap << 1 ?: 1;" "\n"
									"value->%s.data = realloc(value->%s.data, sizeof(*value->%s.data) * value->%s.cap);" "\n"
								"}" "\n"
								"memmove(value->%s.data + 1, value->%s.data, sizeof(*value->%s.data) * value->%s.n);" "\n"
								"value->%s.data[0] = inc_%s_%s(subgrammar), value->%s.n++;" "\n"
							"", name, name,
							name, name,
							name, name, name, name,
							name, name, name, name,
							name, prefix, type, name);
							break;
						}
						
						default:
							TODO;
							break;
					}
				}
				runme;
			}));
			
			fprintf(stream, ""
				"free_%s_%s(subgrammar);" "\n"
				"}" "\n"
			"", prefix, type);
			
			break;
		}
		
		case rik_trie:
		{
			dpvs(this->grammar);
			
			assert(this->grammar);
			
			fprintf(stream, ""
				"{" "\n"
				"struct %s_%s* trie = data.data[--yacc.n, --data.n];" "\n"
				"if (trie->startline < value->startline) value->startline = trie->startline;" "\n"
				"if (value->endline < trie->endline) value->endline = trie->endline;" "\n"
			"", prefix, grammar);
			
			structinfo_foreach(structinfo, ({
				void runme(struct structinfo_node* node)
				{
					const char* const name = node->name->chars;
					
					switch (node->type)
					{
						case snt_token_scalar:
						{
							fprintf(stream, ""
								"if (trie->%s) { free_%s_token(value->%s); value->%s = inc_%s_token(trie->%s); }" "\n"
							"", name, prefix, name, name, prefix, name);
							break;
						}
						
						case snt_token_array:
						{
							fprintf(stream, ""
								"if (trie->%s.n)"
								"{" "\n"
									"while (value->%s.n + trie->%s.n > value->%s.cap)" "\n"
									"{" "\n"
										"value->%s.cap = value->%s.cap << 1 ?: 1;" "\n"
										"value->%s.data = realloc(value->%s.data, sizeof(*value->%s.data) * value->%s.cap);" "\n"
									"}" "\n"
									"memmove(value->%s.data + trie->%s.n, value->%s.data, sizeof(*value->%s.data) * value->%s.n);" "\n"
									"for (unsigned i = 0, n = trie->%s.n; i < n; i++)" "\n"
									"value->%s.data[i] = inc_%s_token(trie->%s.data[i]);" "\n"
									"value->%s.n += trie->%s.n;" "\n"
								"}" "\n"
							"", name,
							name, name, name,
							name, name,
							name, name, name, name,
							name, name, name, name, name,
							name,
							name, prefix, name,
							name, name);
							break;
						}
						
						case snt_grammar_scalar:
						{
							const char* const type = node->grammar.name->chars;
							fprintf(stream, ""
								"if (trie->%s) { free_%s_%s(value->%s); value->%s = inc_%s_%s(trie->%s); }" "\n"
							"", name, prefix, type, name, name, prefix, type, name);
							break;
						}
						
						case snt_grammar_array:
						{
							const char* const type = node->grammar.name->chars;
							
							fprintf(stream, ""
								"if (trie->%s.n)" "\n"
								"{" "\n"
									"while (value->%s.n + trie->%s.n > value->%s.cap)" "\n"
									"{" "\n"
										"value->%s.cap = value->%s.cap << 1 ?: 1;" "\n"
										"value->%s.data = realloc(value->%s.data, sizeof(*value->%s.data) * value->%s.cap);" "\n"
									"}" "\n"
									"memmove(value->%s.data + trie->%s.n, value->%s.data, sizeof(*value->%s.data) * value->%s.n);" "\n"
									"for (unsigned i = 0, n = trie->%s.n; i < n; i++)" "\n"
									"value->%s.data[i] = inc_%s_%s(trie->%s.data[i]);" "\n"
									"value->%s.n += trie->%s.n;" "\n"
								"}" "\n"
							"", name,
							name, name, name,
							name, name,
							name, name, name, name,
							name, name, name, name, name,
							name,
							name, prefix, type, name,
							name, name);
							break;
						}
						
						case snt_scanf_scalar:
						{
							fprintf(stream, ""
								"if (trie->%s) { value->%s = trie->%s; }" "\n"
							"", name, name, name);
							break;
						}
						
						case snt_scanf_array:
						{
							TODO;
							break;
						}
						
						case snt_user_defined:
							break;
						
						default:
							TODO;
							break;
					}
				}
				runme;
			}));
			
			fprintf(stream, ""
				"free_%s_%s(trie);" "\n"
				"}" "\n"
			"", prefix, grammar);
			break;
		}
		
		default:
			TODO;
			break;
	}
	
	if (this->prev)
	{
		reductioninfo_print_source(this->prev, structinfo, grammar, prefix, stream);
	}
	
	EXIT;
}




















