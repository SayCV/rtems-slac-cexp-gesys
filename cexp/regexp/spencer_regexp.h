#ifndef SPENCER_REGEXP_H
#define SPENCER_REGEXP_H
/*
 * Definitions etc. for regexp(3) routines.
 *
 * Caveat:  this is V8 regexp(3) [actually, a reimplementation thereof],
 * not the System V one.
 */

/* T. Straumann, 2003: 
 *
 * This is not compatible with POSIX regexp(3) - therefore,
 * I chose to change the names, prefixing the public ones
 * with 'spencer_'.
 * If you want to use the original names, undefine
 * SPENCER_REGEXP_PREFIX and rename the header and library
 * files.
 */

#define SPENCER_REGEXP_PREFIX

#ifdef SPENCER_REGEXP_PREFIX
#define SPENCER_(name) spencer_ ## name
#else
#define SPENCER_(name) name
#endif


#define NSUBEXP  10
typedef struct SPENCER_(regexp) {
	const char *startp[NSUBEXP];
	const char *endp[NSUBEXP];
	char regstart;		/* Internal use only. */
	char reganch;		/* Internal use only. */
	char *regmust;		/* Internal use only. */
	int regmlen;		/* Internal use only. */
	char program[1];	/* Unwarranted chumminess with compiler. */
} SPENCER_(regexp);

extern SPENCER_(regexp)*
SPENCER_(regcomp)(const char *reg_expression);

extern int
SPENCER_(regexec)(SPENCER_(regexp) *prog, const char *string);

extern void
SPENCER_(regsub)(SPENCER_(regexp) *prog, char *src, char *dst);

extern void
SPENCER_(regerror)(char *msg);

#endif
