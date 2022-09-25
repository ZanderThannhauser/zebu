srcs += ./avl/alloc_tree.c
srcs += ./avl/avl.c
srcs += ./avl/check_balance.c
srcs += ./avl/clear_node.c
srcs += ./avl/clear_tree.c
srcs += ./avl/delete.c
srcs += ./avl/delete_node.c
srcs += ./avl/foreach.c
srcs += ./avl/free_nodes.c
srcs += ./avl/free_tree.c
srcs += ./avl/init_node.c
srcs += ./avl/init_tree.c
srcs += ./avl/insert.c
srcs += ./avl/insert_after.c
srcs += ./avl/insert_before.c
srcs += ./avl/insert_node.c
srcs += ./avl/insert_top.c
srcs += ./avl/rebalance.c
srcs += ./avl/search.c
srcs += ./avl/search_closest.c
srcs += ./avl/unlink_node.c
srcs += ./cmdln/free.c
srcs += ./cmdln/input_path.c
srcs += ./cmdln/make_dependencies.c
srcs += ./cmdln/minimize_lexer.c
srcs += ./cmdln/output_path.c
srcs += ./cmdln/output_prefix.c
srcs += ./cmdln/parser_template.c
srcs += ./cmdln/process.c
srcs += ./cmdln/usage.c
srcs += ./cmdln/verbose.c
srcs += ./debug.c
srcs += ./gegex/add_grammar_transition.c
srcs += ./gegex/add_lambda_transition.c
srcs += ./gegex/add_transition.c
srcs += ./gegex/clone.c
srcs += ./gegex/concat.c
srcs += ./gegex/dfa_to_nfa.c
srcs += ./gegex/dotout.c
srcs += ./gegex/free.c
srcs += ./gegex/from_empty.c
srcs += ./gegex/from_subgrammar.c
srcs += ./gegex/from_token.c
srcs += ./gegex/grammar/free.c
srcs += ./gegex/grammar/new.c
srcs += ./gegex/new.c
srcs += ./gegex/nfa_to_dfa.c
srcs += ./gegex/simplify_dfa.c
srcs += ./gegex/transition/free.c
srcs += ./gegex/transition/new.c
srcs += ./heap/free.c
srcs += ./heap/head.c
srcs += ./heap/is_nonempty.c
srcs += ./heap/len.c
srcs += ./heap/new.c
srcs += ./heap/pop.c
srcs += ./heap/push.c
srcs += ./lex/add_EOF_token.c
srcs += ./lex/add_token.c
srcs += ./lex/build_tokenizer/build_tokenizer.c
srcs += ./lex/build_tokenizer/dfas_to_dfa.c
srcs += ./lex/build_tokenizer/node/compare.c
srcs += ./lex/build_tokenizer/node/free.c
srcs += ./lex/build_tokenizer/node/new.c
srcs += ./lex/find_shortest_accepting.c
srcs += ./lex/free.c
srcs += ./lex/from_node/compare.c
srcs += ./lex/from_node/free.c
srcs += ./lex/from_node/new.c
srcs += ./lex/id_to_dfa.c
srcs += ./lex/minimize_lexer.c
srcs += ./lex/new.c
srcs += ./lex/state/dotout.c
srcs += ./lex/state/free.c
srcs += ./lex/state/new.c
srcs += ./lex/to_node/compare.c
srcs += ./lex/to_node/free.c
srcs += ./lex/to_node/new.c
srcs += ./main.c
srcs += ./memory/smalloc.c
srcs += ./memory/smemdup.c
srcs += ./memory/srealloc.c
srcs += ./misc/break_and_open_path.c
srcs += ./misc/default_sighandler.c
srcs += ./misc/escape.c
srcs += ./misc/format_flags/free.c
srcs += ./misc/format_flags/inc.c
srcs += ./misc/format_flags/new.c
srcs += ./misc/frame_counter.c
srcs += ./misc/sopen.c
srcs += ./misc/sopenat.c
srcs += ./misc/strfandr.c
srcs += ./named/charset/compare.c
srcs += ./named/charset/free.c
srcs += ./named/charset/new.c
srcs += ./named/gegex/compare.c
srcs += ./named/gegex/free.c
srcs += ./named/gegex/new.c
srcs += ./named/regexset/compare.c
srcs += ./named/regexset/free.c
srcs += ./named/regexset/new.c
srcs += ./named/regex/compare.c
srcs += ./named/regex/free.c
srcs += ./named/regex/new.c
srcs += ./named/stringset/compare.c
srcs += ./named/stringset/free.c
srcs += ./named/stringset/new.c
srcs += ./named/structinfo/compare.c
srcs += ./named/structinfo/free.c
srcs += ./named/structinfo/new.c
srcs += ./named/trie/compare.c
srcs += ./named/trie/free.c
srcs += ./named/trie/new.c
srcs += ./named/unsignedset/compare.c
srcs += ./named/unsignedset/free.c
srcs += ./named/unsignedset/new.c
srcs += ./out/dyntable/free.c
srcs += ./out/dyntable/new.c
srcs += ./out/dyntable/print_header.c
srcs += ./out/dyntable/print_source.c
srcs += ./out/dyntable/set.c
srcs += ./out/dynvector/free.c
srcs += ./out/dynvector/new.c
srcs += ./out/dynvector/print_header.c
srcs += ./out/dynvector/print_source.c
srcs += ./out/dynvector/set.c
srcs += ./out/escaped/buffer_driven_header.c
srcs += ./out/escaped/buffer_driven_source.c
srcs += ./out/escaped/fileio_debug_header.c
srcs += ./out/escaped/fileio_debug_source.c
srcs += ./out/escaped/fileio_graphviz_header.c
srcs += ./out/escaped/fileio_graphviz_source.c
srcs += ./out/escaped/fileio_header.c
srcs += ./out/escaped/fileio_passfail_header.c
srcs += ./out/escaped/fileio_passfail_source.c
srcs += ./out/escaped/fileio_source.c
srcs += ./out/escaped/fileio_with_driver_debug_header.c
srcs += ./out/escaped/fileio_with_driver_debug_source.c
srcs += ./out/escaped/fileio_with_driver_header.c
srcs += ./out/escaped/fileio_with_driver_source.c
srcs += ./out/escaped/just_tables_header.c
srcs += ./out/escaped/just_tables_source.c
srcs += ./out/escaped/readline_debug_header.c
srcs += ./out/escaped/readline_debug_source.c
srcs += ./out/escaped/readline_header.c
srcs += ./out/escaped/readline_source.c
srcs += ./out/escaped/readline_with_driver_debug_header.c
srcs += ./out/escaped/readline_with_driver_debug_source.c
srcs += ./out/escaped/readline_with_driver_header.c
srcs += ./out/escaped/readline_with_driver_source.c
srcs += ./out/escaped/really_just_tables_header.c
srcs += ./out/escaped/really_just_tables_source.c
srcs += ./out/lstate_to_id/free.c
srcs += ./out/lstate_to_id/lstate_to_id.c
srcs += ./out/lstate_to_id/new.c
srcs += ./out/out.c
srcs += ./out/print_free_functions.c
srcs += ./out/print_inc_functions.c
srcs += ./out/print_structs.c
srcs += ./out/print_tree_functions.c
srcs += ./out/reducerule_to_id/free.c
srcs += ./out/reducerule_to_id/new.c
srcs += ./out/reducerule_to_id/print_source.c
srcs += ./out/reducerule_to_id/reducerule_to_id.c
srcs += ./out/string_to_id/free.c
srcs += ./out/string_to_id/new.c
srcs += ./out/string_to_id/string_to_id.c
srcs += ./out/unsignedset_to_id/foreach.c
srcs += ./out/unsignedset_to_id/free.c
srcs += ./out/unsignedset_to_id/new.c
srcs += ./out/unsignedset_to_id/print_source.c
srcs += ./out/unsignedset_to_id/unsignedset_to_id.c
srcs += ./out/ystate_to_id/free.c
srcs += ./out/ystate_to_id/new.c
srcs += ./out/ystate_to_id/ystate_to_id.c
srcs += ./parser/charset/0.highest.c
srcs += ./parser/charset/1.complement.c
srcs += ./parser/charset/2.range.c
srcs += ./parser/charset/3.intersect.c
srcs += ./parser/charset/4.xor.c
srcs += ./parser/charset/5.union.c
srcs += ./parser/charset/root.c
srcs += ./parser/grammar/0.highest.c
srcs += ./parser/grammar/1.suffixes.c
srcs += ./parser/grammar/2.subdefinitions.c
srcs += ./parser/grammar/3.concat.c
srcs += ./parser/grammar/4.or.c
srcs += ./parser/grammar/highest/character_literal.c
srcs += ./parser/grammar/highest/gravemark.c
srcs += ./parser/grammar/highest/identifier.c
srcs += ./parser/grammar/highest/numeric_literal.c
srcs += ./parser/grammar/highest/parenthesis.c
srcs += ./parser/grammar/highest/square.c
srcs += ./parser/grammar/highest/string_literal.c
srcs += ./parser/grammar/root.c
srcs += ./parser/main_parse.c
srcs += ./parser/pragma_once/free.c
srcs += ./parser/pragma_once/lookup.c
srcs += ./parser/pragma_once/new.c
srcs += ./parser/pragma_once/node/compare.c
srcs += ./parser/pragma_once/node/new.c
srcs += ./parser/pragma_once/print_dependencies.c
srcs += ./parser/read_charset.c
srcs += ./parser/read_directive.c
srcs += ./parser/read_directive/extra_field.c
srcs += ./parser/read_directive/include.c
srcs += ./parser/read_directive/skip.c
srcs += ./parser/read_directive/start.c
srcs += ./parser/read_fragment.c
srcs += ./parser/read_grammar.c
srcs += ./parser/read_inline_grammar.c
srcs += ./parser/recursive_parse.c
srcs += ./parser/regex/0.highest.c
srcs += ./parser/regex/1.suffixes.c
srcs += ./parser/regex/2.concat.c
srcs += ./parser/regex/3.and.c
srcs += ./parser/regex/4.or.c
srcs += ./parser/regex/highest/character_literal.c
srcs += ./parser/regex/highest/dot.c
srcs += ./parser/regex/highest/identifier.c
srcs += ./parser/regex/highest/numeric_literal.c
srcs += ./parser/regex/highest/parenthesis.c
srcs += ./parser/regex/highest/square.c
srcs += ./parser/regex/highest/string_literal.c
srcs += ./parser/regex/root.c
srcs += ./parser/resolve_grammar_names.c
srcs += ./parser/scope/build_absolute_name.c
srcs += ./parser/scope/declare/charset.c
srcs += ./parser/scope/declare/fragment.c
srcs += ./parser/scope/declare/grammar.c
srcs += ./parser/scope/declare/inline_grammar.c
srcs += ./parser/scope/free.c
srcs += ./parser/scope/get_arena.c
srcs += ./parser/scope/lookup/charset.c
srcs += ./parser/scope/lookup/fragment.c
srcs += ./parser/scope/lookup/inline_grammar.c
srcs += ./parser/scope/new.c
srcs += ./parser/scope/pop.c
srcs += ./parser/scope/private/append_prefix.c
srcs += ./parser/scope/push.c
srcs += ./parser/scope/resolve/grammar.c
srcs += ./parser/tokenizer/free.c
srcs += ./parser/tokenizer/new.c
srcs += ./parser/tokenizer/read_char.c
srcs += ./parser/tokenizer/read_token.c
srcs += ./parser/tokenizer/token_names.c
srcs += ./quack/append.c
srcs += ./quack/foreach.c
srcs += ./quack/free.c
srcs += ./quack/is_nonempty.c
srcs += ./quack/len.c
srcs += ./quack/new.c
srcs += ./quack/pop.c
srcs += ./quack/push.c
srcs += ./regex/accepts.c
srcs += ./regex/add_lambda_transition.c
srcs += ./regex/clone.c
srcs += ./regex/compare_simplified.c
srcs += ./regex/complement.c
srcs += ./regex/dfa_to_nfa.c
srcs += ./regex/dotout.c
srcs += ./regex/free.c
srcs += ./regex/from_charset.c
srcs += ./regex/from_dot.c
srcs += ./regex/from_literal.c
srcs += ./regex/intersect_dfas.c
srcs += ./regex/new.c
srcs += ./regex/nfa_to_dfa.c
srcs += ./regex/set_kind.c
srcs += ./regex/simplify_dfa.c
srcs += ./set/ptr/add.c
srcs += ./set/ptr/clone.c
srcs += ./set/ptr/compare.c
srcs += ./set/ptr/contains.c
srcs += ./set/ptr/discard.c
srcs += ./set/ptr/foreach.c
srcs += ./set/ptr/free.c
srcs += ./set/ptr/get_head.c
srcs += ./set/ptr/inc.c
srcs += ./set/ptr/is_nonempty.c
srcs += ./set/ptr/len.c
srcs += ./set/ptr/new.c
srcs += ./set/string/add.c
srcs += ./set/string/are_equal.c
srcs += ./set/string/foreach.c
srcs += ./set/string/free.c
srcs += ./set/string/inc.c
srcs += ./set/string/is_empty.c
srcs += ./set/string/new.c
srcs += ./set/string/union.c
srcs += ./set/string/update.c
srcs += ./set/unsignedset/add.c
srcs += ./set/unsignedset/foreach.c
srcs += ./set/unsignedset/free.c
srcs += ./set/unsignedset/inc.c
srcs += ./set/unsignedset/len.c
srcs += ./set/unsignedset/new.c
srcs += ./set/unsigned/add.c
srcs += ./set/unsigned/clear.c
srcs += ./set/unsigned/clone.c
srcs += ./set/unsigned/compare.c
srcs += ./set/unsigned/foreach.c
srcs += ./set/unsigned/free.c
srcs += ./set/unsigned/head.c
srcs += ./set/unsigned/inc.c
srcs += ./set/unsigned/len.c
srcs += ./set/unsigned/new.c
srcs += ./set/unsigned/to_string.c
srcs += ./set/unsigned/update.c
srcs += ./string/are_equal.c
srcs += ./string/compare.c
srcs += ./string/free.c
srcs += ./string/inc.c
srcs += ./string/new.c
srcs += ./yacc/build_structinfo.c
srcs += ./yacc/build_tries.c
srcs += ./yacc/calc_firsts.c
srcs += ./yacc/expand_stateinfo.c
srcs += ./yacc/reductioninfo/free.c
srcs += ./yacc/reductioninfo/inc.c
srcs += ./yacc/reductioninfo/new.c
srcs += ./yacc/reductioninfo/print_source.c
srcs += ./yacc/reductioninfo/to_string.c
srcs += ./yacc/stateinfo/add.c
srcs += ./yacc/stateinfo/compare.c
srcs += ./yacc/stateinfo/contains.c
srcs += ./yacc/stateinfo/foreach.c
srcs += ./yacc/stateinfo/free.c
srcs += ./yacc/stateinfo/get_lookaheads.c
srcs += ./yacc/stateinfo/inc.c
srcs += ./yacc/stateinfo/new.c
srcs += ./yacc/stateinfo/node/compare.c
srcs += ./yacc/stateinfo/node/free.c
srcs += ./yacc/stateinfo/node/new.c
srcs += ./yacc/state/add_grammar_transition.c
srcs += ./yacc/state/add_reduce_transition.c
srcs += ./yacc/state/add_transition.c
srcs += ./yacc/state/dotout.c
srcs += ./yacc/state/free.c
srcs += ./yacc/state/new.c
srcs += ./yacc/structinfo/add_grammar_array_field.c
srcs += ./yacc/structinfo/add_grammar_scalar_field.c
srcs += ./yacc/structinfo/add_scanf_scalar_field.c
srcs += ./yacc/structinfo/add_token_array_field.c
srcs += ./yacc/structinfo/add_token_scalar_field.c
srcs += ./yacc/structinfo/add_user_defined_field.c
srcs += ./yacc/structinfo/are_equal.c
srcs += ./yacc/structinfo/compare.c
srcs += ./yacc/structinfo/foreach.c
srcs += ./yacc/structinfo/free.c
srcs += ./yacc/structinfo/inc.c
srcs += ./yacc/structinfo/is_empty.c
srcs += ./yacc/structinfo/new.c
srcs += ./yacc/structinfo/print_source.c
srcs += ./yacc/structinfo/to_hashtagstring.c
srcs += ./yacc/structinfo/to_string.c
srcs += ./yacc/structinfo/update.c
srcs += ./yacc/trie/add_grammar_transition.c
srcs += ./yacc/trie/add_transition.c
srcs += ./yacc/trie/free.c
srcs += ./yacc/trie/new.c
srcs += ./yacc/yacc.c
