#ifndef SAMPGDK_LIKELY_H_
#define SAMPGDK_LIKELY_H_

#if defined __GNUC__
	#define likely(x)    __builtin_expect((x),1)
	#define unlikely(x)  __builtin_expect((x),0)
#else
	#define likely(x)    (x)
	#define unlikely(x)  (x)
#endif

#endif /* !SAMPGDK_LIKELY_H_ */
