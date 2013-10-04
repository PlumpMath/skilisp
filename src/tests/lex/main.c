#include "lex.h"
#include <stdlib.h>

int main(void) {
	char *img;
	int token_type;

	token_type = skil_token(stdin, &img);
	while(token_type >= 0) {
		switch(token_type) {
		case '(':
		case ')':
			printf("%c\n", token_type);
			break;
		case SKIL_TOKEN_ATOM:
			printf("ATOM: %s\n", img);
			free(img);
			break;
		case SKIL_TOKEN_EOF:
			return 0;
			break;
		default:
			printf("Unknown token type %d with value %s!\n",
				token_type, (img)? img :"NULL");
			return 1;
			break;
		}
		token_type = skil_token(stdin, &img);
	}
	/* this is dead code, but it quiets a warning about a missing return
	 * value: */
	return 0;
}
