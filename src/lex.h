#ifndef SKILISP_LEX_H
#define SKILISP_LEX_H
#ifdef __cplusplus
extern "C" {
#endif
/* 
	Interface for a skilisp lexical analyzer.
*/

#include <stdio.h> /* needed for FILE * datatype. */

/*
	Token type constants. see the description of skil_token for more info.
*/
/*
	We start counting at 256 so as not to conflict with any ascii value.
	This allows us to e.g. use '(' as the token identifier for the literal
	character '(', without having to think about whether that collides
	with anything else.

*/
#define SKIL_ATOM 256
#define SKIL_EOF 257

/*
	`skil_token` reads the next token from `input`, returning it's type.

	params:
		input - a FILE* object opened for reading, from which tokens
		will be read.

		img - used to store a string associated with the the token.
		for details, see the section "return value", below. Note
		that for some tokens (e.g. '('), *img may be set to NULL after
		the call, if the type fully captures the information in the
		token.

		if *img is *not* NULL upon return, then it is a malloc-allocated
		string, and the caller is responsible for freeing it.

	return value:
		One of the legal token types, or a negative value, indicating
		an error. The possible error codes are:

		- SKIL_ENOMEM
		- SKIL_BAD_TOKEN

		(see errcode.h).

		The legal token types are:

		'(' - an opening parenthesis. *img will be NULL.
		')' - a closing parenthesis. *img will be NULL.
		SKIL_EOF - The end of file. *img will be NULL.
		SKIL_ATOM - an atom. *img will point to a string representing
			the atom.

	postconditions:
		Either the return value will be one of the (negative) error
		codes mentioned above, or:

		The return value indicates the type of token that was read,
		and the value of *img corresponds to the token type, as
		described under "return value", above.
*/
int skil_token(FILE *input, char **img);

#ifdef __cplusplus
}
#endif
#endif
