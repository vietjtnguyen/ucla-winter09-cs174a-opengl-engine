#ifndef TYPES_H
#define TYPES_H


// TODO (Viet Nguyen): Use these types universally.


// Define NULL for goodness sake
#ifndef NULL
#define NULL 0
#endif


// Specific integer definitions
typedef signed short		int16;
typedef unsigned short		uint16;
typedef signed int			int32;
typedef unsigned int		uint32;
typedef signed __int64		int64;
typedef unsigned __int64	uint64;


// Specific float definitions
typedef float				real32;
typedef double				real64;


// Specific character definitions
typedef char				char8;
typedef wchar_t				char16;


#endif // TYPES_H