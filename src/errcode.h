#ifndef SKILISP_ERRCODE_H
#define SKILISP_ERRCODE_H
#ifdef __cplusplus
extern "C" {
#endif

/*
	Various error codes used throughout skilisp.

	Note that these *must* have negative values, as the typical way to
	check for an error is:

		if(foo() < 0) {
			handle_error();
		}

	Each function that uses these should specify which codes are actually
	possible. The meaning of each code is specified just above its
	definition (in this file).
*/

/* The memory allocator returned an error. */
#define SKIL_ENOMEM -1

/* The input stream contained an invalid token. */
#define SKIL_BAD_TOKEN -2

/* The input stream did not parse correctly. */
#define SKIL_BAD_PARSE -3

#ifdef __cplusplus
}
#endif
#endif
