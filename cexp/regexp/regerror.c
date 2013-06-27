#include <stdio.h>
#include "spencer_regexp.h"

void
SPENCER_(regerror)(s)
char *s;
{
	fprintf(stderr, "regexp(3): %s", s);
}
