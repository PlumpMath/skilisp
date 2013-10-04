#ifndef SKIL_PARSER_H
#define SKIL_PARSER_H
#ifdef __cplusplus
extern "C" {
#endif
/*
	Interface for a skilsip parser.
*/

#include <stdio.h> /* need for FILE * datatype. */

int skil_parse_value(FILE *input, skil_value_t **value);
/*
	`skil_parse_value` reads the next full skilisp value from `input`.

	params:
		input - a FILE* object opened for reading, from which values
		will be read

		value - The address of a pointer in which the address of the
		value will be stored. That is, upon returning from a
		call to `skil_parse_value`, if *value is not NULL, it will be
		a pointer to the value that was read in. The value will be
		malloc() allocated, and the caller will be responsible for
		freeing it. On failure, or if an end of file occurs before any
		token is read in, *value will be NULL.

	return value:

		On a successful call to `skil_parse_value`, the return value
		will be 0. If an error occurs, the value will be one of the
		following (negative) error codes:

		- SKIL_ENOMEM
		- SKIL_BAD_PARSE
		- SKIL_BAD_TOKEN

		If the return value is zero *and* *value is NULL, it is an
		indication that the end of file was reached before any tokens
		were read in.
*/

#ifdef __cplusplus
}
#endif
#endif
