#ifndef SKILISP_VALUE_H
#define SKILISP_VALUE_H
#ifdef __cplusplus
extern "C" {
#endif

/*
	This file contains the basic data definitions for the various types
	within skilisp. Right now this is just conses and atoms, down the line
	we'll add more.
*/

typedef struct skil_cons_t skil_cons_t;
typedef struct skil_value_t skil_value_t;


/*
	These are the possible values for the `tag` field of `skil_value_t`,
	below. In general, if v.tag == SKIL_VALUE_XYZ, then the field `xyz`
	within v.val is the correct value.
*/
enum {
	SKIL_VALUE_CONS,
	SKIL_VALUE_ATOM
};


/*
	A cons cell, or pair.
*/
struct skil_cons_t {
	skil_value_t *fst;
	skil_value_t *snd;
};

struct skil_value_t {
	int tag; /* indicates which of the fields below is valid */
	union {
		skil_cons_t cons;
		char *atom;
	} val;
};

#ifdef __cplusplus
}
#endif
#endif
