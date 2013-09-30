#include "lex.h"
#include "errcode.h"
#include "string_buffer.h"
#include <ctype.h>
#include <stdlib.h>

static int skipws_and_comments(FILE *input);
static int skip_rest_of_line(FILE *input);
int scan_atom(FILE *input, char **img);
int isatomchar(int c);

int skil_token(FILE *input, char **img) {
	int c;

	if(skipws_and_comments(input) < 0) {
		/* end of file */
		return SKIL_EOF;
	}

	c = fgetc(input);
	switch(c) {
	case '(':
	case ')':
		/* these tokens have no value other than their type. */
		*img = NULL;
		return c;
		break;
	case EOF:
		*img = NULL;
		return SKIL_EOF;
	default:
		if(!isprint(c)) {
			/* invalid character; return an error. */
			return SKIL_BAD_TOKEN;
		} else {
			/* put the character back, so that `scan_atom` can read it. */
			ungetc(c, input);
			/* this is an atom, read it in. */
			return scan_atom(input, img);
		}
	};
}

/*
	helper for `skil_token`.

	skips past whitespace and comments, leaving the input stream just before
	the first non-whitespace character outside of a comment. Because it's not
	possible to put an EOF back into the stream, we return -1 to indicate end
	of file. Otherwise, the return value is 0.
*/
static int skipws_and_comments(FILE *input) {
	int c;

		c = fgetc(input);
		while(isspace(c) || c == ';') {
			if(c == ';') {
				if(skip_rest_of_line(input) < 0) {
					return -1;
				}
			}
			c = fgetc(input);
		}
		if(c == EOF) {
			return -1;
		}
		/* Put the last character back; the caller will want to look at it. */
		ungetc(c, input);
		return 0;
}

/*
	helper for `skipws_and_comments`.

	Skips characters in input until it reaches either a '\n', or an EOF.
	If EOF is encountered, returns -1. Otherwise, returns 0 and leaves the
	input the input stream directly after the '\n'.

	in the case of EOF, `fgetc` should continue returning EOF on subsequent
	calls, so there is no need to backtrack. (TODO: verify this.)
*/
static int skip_rest_of_line(FILE *input) {
	int c;

	do {
		c = fgetc(input);
	} while(c != '\n' && c != EOF);
	if(c == EOF) {
		return -1;
	}
	return 0;
}

/*
	helper for `skil_token`

	preconditions:
		`input` is a FILE object open for writing, pointing at the start of an
		atom.

	postconditions:
		scans in the atom, stores a pointer to it in *img, and returns SKIL_ATOM.

	The following errors may occur, in which case *img will be NULL:
		SKIL_ENOMEM
*/
int scan_atom(FILE *input, char **img) {
	skil_string_buffer_t buf;
	int c;

	if(skil_string_buffer_init(&buf) < 0) {
		return SKIL_ENOMEM;
	}

	c = fgetc(input);
	while(isatomchar(c)) {
		if(skil_string_buffer_putc(&buf, c) < 0) {
			free(buf.buf);
			return SKIL_ENOMEM;
		}
		c = fgetc(input);
	}

	*img = buf.buf;
	ungetc(c, input);
	return SKIL_ATOM;
}

int isatomchar(int c) {
	return
		isprint(c) &&
		!isspace(c) &&
		c != ';' &&
		c != '(' &&
		c != ')' &&
		c != EOF;
}
