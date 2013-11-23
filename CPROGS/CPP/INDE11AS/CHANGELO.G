Mon Sep 11 20:03:56 1989  Jim Kingdon  (kingdon at apple-gunkies.ai.mit.edu)

	* io.c (diag): Add "char *msg".

	* Makefile (indent.tar.Z): Use -h.

	* Makefile (indent.tar.Z): Fix so it uses dist-indent.

Tue Sep  5 21:11:00 1989  Jim Kingdon  (kingdon at apple-gunkies.ai.mit.edu)

	* indent.c (main, case lparen): Do not call dump_line on '{' if
	line is empty.

Sun Sep  3 13:37:17 1989  Jim Kingdon  (kingdon at apple-gunkies.ai.mit.edu)

	* args.c: Remove PRO_STDIN and have -st just set use_stdinout.
	indent.c (main): Check use_stdinout.
	indent_globs.h: Add use_stdinout

	* indent.c (main, case lbrace): Set parser_state_tos->in_or_st
	to false.

Sat Sep  2 20:53:11 1989  Jim Kingdon  (kingdon at apple-gunkies.ai.mit.edu)

	* parse.c (reduce): Tidy up comment before reduce.

	* lexi.c (lexi): Change (*tp == ';') to (*tp == ';' || *tp == ',')

	* lexi.c: Change #include "ctype.h" to #include <ctype.h>

	* io.c (count_spaces): Replace quoted actual ^H in source file
	with 010.

	* various: Remove formfeeds (and one spurious ^\ that snuck into
	a comment in parse.c).

	* io.c (dump_line): Convert random text after #else and #endif
	to comments.

	* various: Remove unnecessary semicolons after "}".

	* indent.c (main, case comment) Remove unnecesary label proc_comment.

	* indent.c (main): Allow space between '#' and preprocessor
	directives (two changes: 1. skip over the space; 2. change
	strncmp's with "#if", "#else", and "#endif" to compare with
	"if", etc. instead.).

	* indent.c (main): Break declarations after comma if the
	declaration is getting too long.

	* args.c (set_option, PRO_INT): Check for !isdigit, not just
	for end of string.

	* args.c (option_source): Add variable and code using it.

	* indent.c (main, search_brace, case lbrace): Put braces around
	"else" code in "if (btype_2)".

Thu Aug 31 20:25:27 1989  Jim Kingdon  (kingdon at apple-gunkies.ai.mit.edu)

	* indent_globs.h: Replace check_size with check_{code,com,lab}_size.
	everywhere: Replace calls to check_size with calls to
	check_{code,com,lab}_size.

	* indent.c (main, case rparen): Do not set last_token_ends_sp
	if it is the while of a do-while.

	* indent.c (main, search_brace, case lbrace): If not BTYPE_2,
	put '{' at end of save_com.

	* indent.c (main): Dynamically allocate di_stack.

	* globs.c, indent_globs.h (mymemcpy): New function.
	indent.c: Use it instead of memcpy.

	* indent.c (main, case lparen): if encountered '{' in initializer
	list, force it to a new line.

Tue Aug 22 01:12:53 1989  Jim Kingdon  (kingdon at hobbes.ai.mit.edu)

	* indent.c (main, case comment): Check for end of file (indicating
	an unclosed comment).

	* args.c (pro, "gnu"): change -di0 to -di1.

	* lexi.c: Use gperf.

Thu Aug 10 18:21:39 1989  Jim Kingdon  (kingdon at hobbes.ai.mit.edu)

	* indent.c (bakcopy): Use mode 0666 for creat

	* indent.c (indent, case newline): Add "else_or_endif = false;"

Sun Aug  6 17:32:54 1989  Jim Kingdon  (kingdon at hobbes.ai.mit.edu)

	* indent.texinfo (Comments): Clarify that -gnu and -kr
	include -nfca.

Thu Aug  3 18:23:17 1989  Jim Kingdon  (kingdon at susie)

	* args.c (pro): Added flags -cs, -ncs.
	indent_globs.h: Added variable cast_space
	indent.c (main) at rparen: Add test for cast and cast_space.
	indent.texinfo (Statements, Option summary): Document -cs.

	* lexi.c (lexi): In the code that checks for keywords, comment
	out performance hack that doesn't work right.

	* indent.c (main): Don't set parser_state_tos->last_token if
	the token is a formfeed.

	* io.c (read_stdin): Remove unused variables i and pos.

	* indent.c (main): Remove unnecessary label do_binary.

	* many places: Clean up int<->enum conversions to avoid
	compiler warnings (and to make debugging easy by declaring
	everything as an enum which should be one).

	* indent.c (main): Initialize last_token_ends_sp to 0.

	* io.c (read_stdio): Change ch from char to int so that EOF
	will work when it doesn't fit in a char.

Wed Aug  2 18:37:10 1989  Jim Kingdon  (kingdon at hobbes.ai.mit.edu)

	* lexi.c (specials): Correct misspelling of "typedef".

Sat Jul 15 19:37:56 1989  Jim Kingdon  (kingdon at hobbes.ai.mit.edu)

	* globs.c: Change copyright notice to be consistent with other
	files. 

Wed Jul 12 00:16:59 1989  Jim Kingdon  (kingdon at apple-gunkies.ai.mit.edu)

	* Makefile: Change it so that all files in the tar file are in
	a directory dist-indent.

	* Remove LIBC from Makefile.

	* Released GNU indent 1.0

	* io.c: Remove #ifdef USG and always include <fcntl.h>.

	* version.h:  New file containing version number.
	Makefile:  Add version.h.
	args.c (pro, set_option): Add -version option and PRO_PRSTRING.
	indent.texinfo (Miscellaneous options): Document -version.

Tue Jul  4 22:19:36 1989  Jim Kingdon  (kingdon at apple-gunkies.ai.mit.edu)

	* indent.c (main): Put call to bakcopy() inside if (output == 0)

	* io.c: Include <fcntl.h> rather than <sys/file.h> (#ifdef USG)

	* indent_globs.h, io.c, lexi.c: Replace realloc with xrealloc

	* indent_globs.h, parse.c, args.c, io.c: Remove function
	prototypes, void *, (read_file)variable size array.

Mon Jul  3 15:04:29 1989  Jim Kingdon  (kingdon at apple-gunkies.ai.mit.edu)

	* Everywhere: use xrealloc and xmalloc instead of realloc and malloc.

	* globs.c: Give the program name in the error messages.

	* io.c (diag): Change error messages to <filename>: <line #>: form.

	* lexi.c (lexi): Rewrite string/character constant copying
	loop to fix problems with backslashes.  Change error message
	for unterminated constant to use terminology consistent with
	K&R and to use the diag routine.

Sun Jul  2 16:51:23 1989  Jim Kingdon  (kingdon at apple-gunkies.ai.mit.edu)

	* parse.c (parse): Replaced parser_state_tos->tos++ with inc_pstack
	in one place it had been missed before.

	* parse.c, indent_globs.h: Move Inc_pstack to parse.c and make
	it a function to facilitate debugging (it is probably getting
	a bit big to be inline anyway).

	* indent_globs.h: Have all of the parser stacks (p_stack, il,
	and cstk) share a common allocated size (p_stack_size).
	(Inc_pstack) realloc them all, not just p_stack.
	indent.c (main): Change all references to {il,cstk}_size to
	p_stack_size.

	* indent.c (main): In initialization of
	parser_state_tos->p_stack, etc., multiply size given to malloc
	by sizeof (@var{whatever}).

        * indent_globs.h (Inc_pstack): multiply size given to realloc
	by sizeof (enum codes).
	
	* indent.c (main): In the main case statement, in the lparen
	case, change parser_state_tos->p_stack =
	xrealloc(parser_state_tos, . . . to . . . xrealloc
	(parser_state_tos->p_stack, . . .
	                 ^^^^^^^^^
        This fixes a bug which caused core dumps.

Sat Jul  1 23:02:50 1989  Jim Kingdon  (kingdon at apple-gunkies.ai.mit.edu)

	* args.c: Add -kr option to pro.

Fri Jun 30 14:06:50 1989  Jim Kingdon  (kingdon at hobbes.ai.mit.edu)
	(actually these changes were made some time ago)
	* indent.c: Treat va_dcl specially so we indent it right.

	* lexi.c (lexi): Make it so that initializations will get
	lined up correctly by uncommenting out code that says
	code = ps.block_init ? lparen : lbrace;
	
	* indent_codes.h: eliminated and put into indent_globs.h.
	Converted from #defines to enum.
	lexi.c, parse.c, indent.c, perhaps others: various variables changed
	to enum	codes from int.

	* args.c: Add explicit flag to pro, and to set_option().
	Add support for PRO_SETTINGS.  Streamline pro to eliminate
	PRO_SPECIAL.  Use enum for PRO_*.
	
	* indent.c (bakcopy): Give error from perror instead of vague
	error message.
	
	* indent.c (bakcopy): bakfile dynamically allocated.

	* io.c (dump_line): fix bug involving a formfeed on a line of
	its own.

	* io.c (read_file, fill_buffer): read input file into memory.
	change token, procname to be a pointer into input file.
	indent.c (main): use token as pointer into input file.  Move
	troff mode string constant stuff here from fill_buffer.
	io.c, indent.c: change save_com to be realloc'd as necessary.

	* indent.c (main): Change it so 'indent foo bar baz' gives an
	error message without clobbering bar.

Tue Jun 27 03:10:53 1989  Jim Kingdon  (kingdon at apple-gunkies.ai.mit.edu)

	Note: Up until this point this ChangeLog is fairly sketchy.
	From here on I promise to log all changes.

	* all files: Change the parser_state structure and the stack
	of parser states to be a dynamically allocated linked list
	instead of a 5 member structure.  Also change the p_stack, il,
	cstk, and paren_indents arrays within the parser state to be
	dynamically allocated and realloc'd as necessary.

Wed Jun 21 21:28:37 1989  Roland McGrath  (roland at hobbes.ai.mit.edu)

	* indent_globs.h: Use ANSI token pasting #ifdef __STDC__.
	(check_size): Check the return value of realloc and exit if it's nil.

	* lexi.c (user_specials{_max,_idx}): New variables for user-defined
	specials.
	(addkey): Define new specials in user_specials, which is dynamically
	expanded if necessary.

Thu Jun  8 15:45:07 1989  Jim Kingdon  (kingdon at spiff)

	* Add -fca option.  If -fca is set, comments will be reformatted.
	If -nfca is set, comments will be left untouched (as with
	comments starting with '*').  The default is -fca.

	* Add -cp option.  The column number for comments to the right
	of #else and #endif.  The default is -cp33.

	* Add -ss and -nss option.  When specified, -ss places a space
	before a semicolon when it occurs after a while or for, e.g.
	  while (*p++ == ' ') ;
	whereas -nss would give
	  while (*p++ == ' ');
	The default is -nss.

Tue Jun  6 10:43:20 1989  Jim Kingdon  (kingdon at hobbes.ai.mit.edu)

	* Add -bli option
	This allows you to indent a compound statement within an if,
	while, etc., e.g. -bli2 gives
	if (foo == bar)
	  {
	    baz = 2;
	  }
	whereas -bli0 (the default) gives
	if (foo == bar)
	{
	  baz = 2;
	}

	* Make -ip numeric
	The -ip parameter now is numeric--the value is the number of
	spaces to indent them.  The -d, -ci, and -cli parameters are also
	now in spaces rather than indent levels.

Local Variables:
mode: indented-text
left-margin: 8
version-control: never
End:
