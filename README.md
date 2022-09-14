
# Zebu

## Introduction

Zebu is a LL parser-generator written in C. It does the work of both GNU bison &
flex by allowing the user to put regular expressions directly in the grammar
description. The parser and the tokenizer(s) are generated simultaneously,
resulting in a **context-sensitive** tokenizer. A tokenizer is generated to
recognize only the tokens that would be valid to read next for each parser state.
This enables reading multiple languages with the same parser, with perhaps
different keywords or comment-style. (CSS embded in HTML, for instance)

## Input file Specification

The input file lists a series of grammar rules and directives. Two grammars
cannot have the same name, even if defined in seperate files.

### List of Directives

 - `%start`: A grammar rule follows, ending with a semicolon. This grammar
    follows all the regular behavior of grammar rules, 
 - `%skip`: A regular expression follows, ending with a semicolon. This regular
    expression describes the characters or strings that should be ignored by
    the tokenizer when scanning for tokens. Note that the specified "skip"
    pattern will only be effective to the tokens described *after* the
    directive is given. Common usages are listed below:
   - `%skip: [' ', '\t', '\n];` (Ignores space, tab and newline characters)
   - `%skip: [' ', '\t', '\n] | "#"[~"\n"]*"\n"` (Ignores characters listed
     above, in addition to skipping anything bewteen a pound (#) and a newline)
 - `%include`: Gives a path to read using either `"path"` or `<path>` syntax.
    The former will resolve the path relative to the current file, and the latter
    will resolve the path relative to the file zebu was given on the command-line.
    Each file does *not* have its own namespace. All of the defined character
    sets, tokens, and grammars will be copied into the global scope.
    A file `include`d more than once will not be read more than once, this is
    detected by using `stat(2)`'s `st_dev` and `st_ino` values.

### Regular Expression Language

#### Examples

### Grammar Language

#### Examples

### Languages

## More about Token Processing

Each of the resultant tokenizers can be "minimized" into one monolithic
tokenizer with the `-l` (`--minimize-lexer`) command-line argument. This option
is not enabled by default, because it can sometimes make the generation
significantly slower.

## More about Grammar Processing

## Parser Templates

## Future Features

 - Way of articulating in the input file how to handle shift-reduce errors,
   perhaps something not unlike the way GNU Bison or Yacc deals with them:
   (Tokens having a "precedence", if the last token of a production rule has a
    higher precedence than the lookahead token: reduce, otherwise shift.)
 - Something to let you insert custom C code into the tokenizer to change which
   token the tokenizer reports detecting, an application for this would be to
   get Zebu to differeate bewteen C variable usage and a `typedef`-ed type usage.

