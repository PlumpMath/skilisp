#include "string_buffer.h"
#include <stdlib.h>

#define STRING_BUF_START_CAP 16

int skil_string_buffer_init(skil_string_buffer_t *buf) {
	buf->cap = STRING_BUF_START_CAP;
	buf->buf = malloc(sizeof(char) * buf->cap);
	if(!buf->buf) {
		return -1;
	}
	buf->buf[0] = '\0';
	buf->len = 0;
	return 0;
}

int skil_string_buffer_putc(skil_string_buffer_t *buf, char c) {
	if(buf->len + 1 >= buf->cap) {
		/* buffer is full, allocate more memory. */
		char *newbuf = realloc(buf->buf, buf->cap * 2);
		if(!newbuf) {
			return -1;
		}
		buf->buf = newbuf;
		buf->cap *= 2;
	}
	buf->buf[buf->len] = c;
	buf->buf[buf->len+1] = '\0';
	buf->len++;
	return 0;
}
