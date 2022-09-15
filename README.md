
# Zebu

## Introduction

Zebu is a LL parser-generator written in C. It does the work of both GNU bison &
flex by allowing the user to put regular expressions directly in the grammar
description. The parser and the tokenizer(s) are generated simultaneously,
resulting in a **context-sensitive** tokenizer. A tokenizer is generated to
recognize only the tokens that would be valid to read next for each parser state.
This enables reading multiple languages with the same parser, with perhaps
different keywords or comment-style. (CSS embedded in HTML, for instance)

## Command-Line Arguments (Usage):

 - `-i` (`--input`): Specifies path to input file.
 - `-o` (`--output`): Specifies path for output files. *without file extension*.
   For instance, if one wanted zebu to produce "dir/foo.c" and "dir/foo.h", one
   would invoke zebu with `-o dir/foo`.
 - `-p` (`--prefix`): Sets the prefix the generated code should have it's
   non-`static` functions and globals. This is useful to avoid symbol-conflicts
   when linking multiple parsers generated by zebu. The default value is "zebu".
 - `-t` (`--template`): Sets which parser-template zebu should use when
   generating it's output. The default value is "just-tables".
 - `-l` (`--minimize-lexer`): Tells zebu to combine and simplify all tokenizers
   generated across all parser-contexts. This operation may take some time
   depending on the language. This option is disabled by default.
 - `-v` (`--verbose`): Enables status-update/progress-percentage print-outs
  for the most time-consuming algorithms: NFA-to-DFA, DFA-simplification,
  Lexer-Minimization and LL parser-generation.
 - `-h` (`--help`): Prints this help message.

## Input file Specification

The input file lists a series of grammar rules and directives. Two grammars
cannot have the same name, even if defined in separate files.

### List of Directives

 - `%start`: A grammar rule follows, ending with a semicolon. This grammar
    follows all the regular behavior of grammar rules, 
 - `%skip`: A regular expression follows, ending with a semicolon. This regular
    expression describes the characters or strings that should be ignored by
    the tokenizer when scanning for tokens. Note that the specified "skip"
    pattern will only be effective to the tokens described *after* the
    directive is given. Common usages are listed below:
    - `%skip: [' ', '\t', '\n];` (Ignores space, tab and newline characters)
    - `%skip: [' ', '\t', '\n] | "#"[!"\n"]*"\n"` (Ignores whitespace characters
       above, in addition to skipping shell-style comments)
    - `%skip: [' ', '\t', '\n] | "//"[!"\n"]*"\n"` (Ignores whitespace characters
       above, in addition to skipping C-style comments)
    - `%skip: [128 - 255];` (Ignores all bytes with their high-bit set)
 - `%include`: Gives a path to read using either `"path"` or `<path>` syntax.
    The former will resolve the path relative to the current file, and the latter
    will resolve the path relative to the file zebu was given on the command-line.
    Each file does *not* have its own namespace. All of the defined character
    sets, tokens, and grammars will be copied into the global scope.
    A file `include`d more than once will not be read more than once, this is
    detected by using `stat(2)`'s `st_dev` and `st_ino` values.

### Character Set Expression Context

Inside of either a regular-expression or grammar-rule context, one can enter the
character-set-expression context using `'['` and `']'`. One can define a name
as representing the result of a character-set expression to a name
using `[name]: value;` syntax.

Either C-style single-quote character literals or C-style integer-literals can
be used inside a character set to describe a character. For example, the letter
'a' can be indicated by `'a'`, or `97`, or `0x61`.

Remember that one can also refer to the value of a defined character-set by
name, inside of other character-set expressions. The referenced character-set
must be defined before it can be used.

#### Operators:

A list of operators and their meaning is listed below. Remember that parenthesis
(`(` & `)`) can be used to raise the precedence of low-precedence operators.

1. `!$1`: Unary operator. Returns the complement of the given character-set.
2. `$1 - $2`: Binary operator, not associative. If given two Literals, returns a
   character-set containing all of the characters between the first character
   literal up-to-and-including the second character literal. If the first
   operand is a character-set, it will use the minimum character contained in
   the set. If the second operand is a is character-set, it will use the
   maximum character contained in the set.
   Example: `['a' - 'c']` yields `['a', 'b', 'c']`.
   Example: `[('a', 'b') - ('c', 'd')]` yields `['a', 'b', 'c', 'd']`.
3. `$1 & $2`: Binary operator, intersection, left-associative.
   Returns a character-set of all the elements
   that are contained in *both* of the two given character-sets.
   Example: `[('a','b','c') & ('b','c','d')]` yields `['b', 'c']`.
   Example: `[('a','b','c') & !'a']` yields `['b', 'c']`.
4. `$1 ^ $2`: Binary operator, symmetric-difference, Left-associative.
   Returns a character-set of all the elements that are
   contained in *only one* of the two given character-sets.
   Example: `[('a','b','c') ^ ('b','c','d')]` yields `['a', 'd']`.
5. `$1 | $2` or `$1, $2` or `$1 $2`: Binary operator, union, left-associative.
   Returns a character-set of all elements that
   are contained in *either* given character-set. This is also the default
   behavior if no operator is given between two character-sets.
   Example: `[('a','b','c') | ('b','c','d')]` yields `['a', 'b', 'c', 'd']`.

#### Examples:

 - `['a' 'b' 'c']` or `['a', 'b', 'c']` or `['a' | 'b' | 'c']` or `['a' - 'c']`
    or `[97 - 99]`: Describes a character-set containing the letters 'a', 'b'
    and 'c'.
 - `[('a', 'b') ^ ('b', 'c')]`: Describes a character-set containing the letters
    'a' and 'c'.
 - `[!(!('a' - 'c') & !('b' - 'd'))]` or `['a' - 'c' | 'b' - 'd']`: Describes
    the character-set containing 'a', 'b', 'c' and 'd'.
 - `[!(!('a' - 'c') | !('b' - 'd'))]` or `['a' - 'c' & 'b' - 'd']`: Describes
    the character-set containing 'b' and 'c'.
 - `['a'-'z' & !('a','e','i','o','u')]`: Describes a character-set containing
    all English consonants.
 - `[0 - 127]`: Describes any ASCII character.

### Regular Expression Language

Inside of a grammar-rule context, one can enter the regular-expression context
using gravemarks ('\`'). One can also define a name as representing the value
of a regular-expression to using `\`\[name\]\`: value;` syntax.

Either C-style character-literals, integer-literals, or string-literals can be
used in regular-expressions. The dot ('.') literal can be used as a shorthand
for `[0 - 255]`, matching any valid next character.

Square-brackets ('[ ]') can be used to enclose a character-set expression,
described above.

Remember that one can also refer to the value of a defined regular-expression by
name, inside of other regular expressions. The referenced regular-expression
must be defined before it can be used.

#### Operators

A list of operators and their meaning is listed below. Remember that parenthesis
(`(` & `)`) can be used to raise the precedence of low-precedence operators.

1. `$1?`, `$1*`, `$1+`, `$1{N}`, `$1{N, }`, `$1{, N}`, `$1{N, M}`: Unary
   Operators, indicates repetition. Returns a regular expression that would match
   strings that would match the given regular-expression to repeat 0 or 1 times,
   0 or more times, 1 or more times, `N` times ('N' must be a numeric literal),
   `N` or more times, up to `N` times (inclusive), between `N` to `M` times
   (inclusive, 'M' must be a numeric literal), respectively.
   Example: `'a'?` would match "", "a".
   Example: `'a'*` would match "", "a", "aa", "aaa", etc.
   Example: `'a'+` would match "a", "aa", "aaa", etc.
   Example: `'a'{3}` would match "aaa".
   Example: `'a'{,3}` would match "", "a", "aa", "aaa".
   Example: `'a'{3,}` would match "aaa", "aaaa", "aaaaa", etc.
   Example: `'a'{2,4}` would match "aa", "aaa", "aaaa".
2. `$1 $2`: Binary operator, indicates concatenation/juxtaposition,
   left-associative. Returns
   a regular expression that would match the strings made of concatenating all
   the strings that would match the first given regular-expression with all
   the strings that would match the second given regular-expression.
   Example: `'a'+ 'b'+` would match "ab", "aab", "abb", etc.
3. `$1 & $2` or `$1 & !$2`: Binary operators, intersection and difference
   respectively, left-associative. If the intersection operator was used, this
   expression returns a regular expression that matches the strings that would
   be matched by *both* the first and the second given regular expressions. If
   the difference operator was used, this expression returns a regular
   expression that matches the strings that would be matched by the first, but
   not the second given regular expression.
   Example: `"aa"* & "aaa"*` would match "", "aaaaaa", "aaaaaaaaaaaa", etc.
   Example: `"aa"* &! "aaa"*` would match "aa", "aaaa", "aaaaaaaa", etc.
4. `$1 | $2`: Binary operator, union, left-associative. Returns a regular
   expression that matches the strings that would be matched by either the
   first or second given regular expression.
   Example: `"a" | "b"` would match "a" or "b".
   Example: `("a" | "b")*` would match "", "a", "b", "ab", "ba", etc.

#### Examples:

 - `[!'b']* 'b' [!'b']* 'b' [!'b']*`: Would match any string containing exactly
    two 'b's.
 - `['0'-'9']+ ('.' ['0'-'9']*)?`: Would match any decimal digits with possibly
    digits past the decimal-point.
 - `'a'+'b'+'c'+ & (..)*`: Describes all even-length strings with one-or-more
    'a's, one-or-more 'b's, and one-or-more 'c's, consecutively.
 - `'a'+'b'+'c'+ &! 'a''b'+'c'`: Describes all strings with one-or-more
    'a's, one-or-more 'b's, and one-or-more 'c's, but that either 'a' or 'c'
    must be repeated more than once.
    'c'.
 - `'a'+'b'+'c'+ &! "abc"`: Describes all strings with one-or-more
    'a's, one-or-more 'b's, and one-or-more 'c's, but at least one letter must
    be repeated more than once.
 - `'a'? 'b'? 'c'?`: Describes all the alphabetically-sorted strings made only
   from 'a', 'b' and 'c' where no letter can be repeated.
 - Describes all UTF8-encoded strings:
```C
( [0x00 - 0x7F] [0x80 - 0xBF]{0}
| [0xC0 - 0xDF] [0x80 - 0xBF]{1}
| [0xE0 - 0xEF] [0x80 - 0xBF]{2}
| [0xF0 - 0xF7] [0x80 - 0xBF]{3}
| [0xF8 - 0xFB] [0x80 - 0xBF]{4}
| [0xFC - 0xFD] [0x80 - 0xBF]{5} )*
```

### Grammar Rule Expressions

Also Talk about tags.

#### Operators

#### Examples

 - `A: ('!' | '(' A ')')+;`
 - `B: ('a' 'b' 'c')* 'a' 'b'`

### Example Languages

This section provides a small catalog of sample input files for zebu.

#### JSON

```C
%skip: ' ' | '\t' | '\n';

%start: value #value;

`string`: '\"' ['a' - 'z']+ '\"';

keyvalue: `string` #key ":" value #value;

value
	: "true"  #boolean
	| "false" #boolean
	| `['0' - '9']+` #number
	| `string` #string
	| "[" value #elements[] ("," value #elements[])* "]"
	| ("{" keyvalue #dict[] ("," keyvalue #dict[])* "}")
	;
```

#### CSV

```C
`cell`: [~',','\"','\n']* ([~',','\"','\n']* '\"' (('\"' '\"') | [~'\"','\n'])* '\"')* [~',','\"','\n']*;

row: `cell` #cells[] (',' `cell` #cells[])* `'\n'+`;

%start: (row #rows[])+;
```

#### Math Expressions

```C
%skip: ' ';

highest: `['0' - '9']+` #literal | '(' root #subexpression ')' ;

multiply: highest #base ('*' highest #multiplymes[] | '/' highest #dividemes[])*;

addition: multiply #base ('+' multiply #addmes[] | '-' multiply #subtractmes[])*;

root: addition #root;

%start: root #root;
```

## Implementation Details: Tokenizer

## Implementation Details: Grammar Rules

## Parser Templates

## Future Features

 - There should be an option (enabled by default) to skip the strings matched
   by the `%skip` pattern, **without** prepending them to the next token.
   Possible approaches:
   - Describe whitespace as it's own token to the tokenizer-generator, marking
     the token_id to be included in each tokenizer featuring the tokens declared
     after the `%skip`, and making a new table for run-time to be able to check
     if the matched token is whitespace and it should rerun for the next token.
   - Include whitespace as part of the state machines for the token, but mark
     the states that return back from processing as ones that should clear
     the tokenizer's buffer.
 - Way of articulating in the input file how to handle shift-reduce errors,
   perhaps something not unlike the way GNU Bison or Yacc deals with them:
   (Tokens having a "precedence", if the last token of a production rule has a
    higher precedence than the look-ahead token: reduce, otherwise shift.)
 - Something to let you insert custom C code into the tokenizer to change which
   token the tokenizer reports detecting, an application for this would be to
   get Zebu to differentiate between C variable usage and a `typedef`-ed type usage.














