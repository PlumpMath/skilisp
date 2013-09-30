#ifndef SKILISP_STRING_BUFFER_H
#define SKILISP_STRING_BUFFER_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

/*
	Expandable string buffers.

	Overview

	string buffers are a datatype which allow the user to incrementally
	build up a string in a buffer, without having to worry too much about
	the memory management.

	There are two functions, `skil_string_buffer_init`, and
	`skil_string_buffer_putc`. init is used to set up a string buffer -
	it's argument should be an uninitialized string buffer.

	Once the buffer has been initialized, putc can be used to add
	characters to the buffer.

	Both of these functions will return 0 on success, or -1 in the event
	of a failed called to malloc.

	At all times after a call to init (including after a failed call to
	putc), the `buf` member points to a valid NUL terminated string
	allocate on the heap, which represents the contents of the buffer. The
	user is responsible for freeing this memory when finished with it.

	A typical use case is something like the following (Though please note
	that this example doesn't do proper error checking):

	skil_string_buffer_t buffer;
	skil_string_buffer_init(&buffer);
	while(condition) {
		skil_string_buffer_putc(&buffer, c);
		c = fgetc(file);
	}
	return buf.buf;

*/

typedef struct {
	char *buf;
	size_t cap, len;
} skil_string_buffer_t;

int skil_string_buffer_init(skil_string_buffer_t *buf);
int skil_string_buffer_putc(skil_string_buffer_t *buf, char c);

#ifdef __cplusplus
}
#endif
#endif
