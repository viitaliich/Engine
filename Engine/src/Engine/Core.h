#pragma once

// Macro either dllexport or dllimport depending on whether we are building or not this dll file.

#ifdef EG_PLATFORM_WINDOWS
	#ifdef EG_BUILD_DLL
		#define ENGINE_API __declspec(dllexport)		// Windows only
	#else
		#define ENGINE_API __declspec(dllimport)
	#endif
#else 
	#error Engine only supports Windows.
#endif

// if bit at position X is needed, 1 moves left on X bits
#define BIT(x) (1 << x)