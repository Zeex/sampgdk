#ifndef SAMPGDK_STDBOOL_H
#define SAMPGDK_STDBOOL_H

#if !defined __cplusplus
	#if defined __STDC__ && defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L
		/* have a C99 compiler */
		#include <stdbool.h>
	#else
		typedef unsigned char bool;
		#define true 1
		#define false 0
	#endif
#endif 

#endif /* !SAMPGDK_STDBOOL_H */
