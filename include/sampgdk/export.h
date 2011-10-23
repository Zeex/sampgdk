#ifndef SAMPGDK_EXPORT_H
#define SAMPGDK_EXPORT_H

#undef SAMPGDK_EXPORT
#undef SAMPGDK_CALL

#if defined _WIN32 || defined WIN32
	#define SAMPGDK_CALL __stdcall
#endif

#if defined IN_SAMPGDK 
	#if !defined SAMPGDK_STATIC
		#if defined WIN32 || defined _WIN32
			#define SAMPGDK_EXPORT __declspec(dllexport)
		#else
			#define SAMPGDK_EXPORT __attribute__((visibility("default")))
		#endif 
	#endif
#else // !IN_SAMPGDK
	#if !defined SAMPGDK_STATIC
		#if defined WIN32 || defined _WIN32
			#define SAMPGDK_EXPORT __declspec(dllimport)
		#endif
	#endif
#endif // IN_SAMPGDK

#if !defined SAMPGDK_EXPORT
	#define SAMPGDK_EXPORT
#endif
#if !defined SAMPGDK_CALL
	#define SAMPGDK_CALL
#endif

#endif // !SAMPGDK_EXPORT_H
