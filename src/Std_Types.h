#ifndef STD_TYPES_H
#define STD_TYPES_H

/* Boolean type and literals */
typedef unsigned char bool;
#define TRUE  ((bool)1)
#define FALSE ((bool)0)

/* Integer types (unsigned) */
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

/* Integer types (signed) */
typedef signed char sint8;
typedef signed short sint16;
typedef signed int sint32;
typedef signed long long sint64;

/* Floating-point types */
typedef float float32;
typedef double float64;

#endif /* STD_TYPES_H */