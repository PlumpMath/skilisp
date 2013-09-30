#ifndef SKILISP_ERRCODE_H
#define SKILISP_ERRCODE_H
#ifdef __cplusplus
extern "C" {
#endif

/* The memory allocator returned an error. */
#define SKIL_ENOMEM -1
/* The input stream contained an invalid token. */
#define SKIL_BAD_TOKEN -2

#ifdef __cplusplus
}
#endif
#endif
