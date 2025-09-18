/**
 * @file Std_Types.h
 * @brief Standard type definitions for embedded systems
 * 
 * This file provides platform-independent type definitions that should be used
 * throughout the project to ensure portability and consistency.
 */

#ifndef STD_TYPES_H
#define STD_TYPES_H

/**
 * @defgroup boolean_types Boolean Types
 * @{
 */

/**
 * @brief Boolean type for true/false values
 * 
 * Use this type for logical true/false values rather than using integers directly.
 * Always use the TRUE and FALSE macros for boolean values.
 */
typedef unsigned char bool;

/** Boolean true value (1) */
#define TRUE  ((bool)1)

/** Boolean false value (0) */
#define FALSE ((bool)0)

/** @} */ // end of boolean_types

/**
 * @defgroup unsigned_types Unsigned Integer Types
 * @{
 */

/** 8-bit unsigned integer (0 to 255) */
typedef unsigned char uint8;

/** 16-bit unsigned integer (0 to 65,535) */
typedef unsigned short uint16;

/** 32-bit unsigned integer (0 to 4,294,967,295) */
typedef unsigned int uint32;

/** 64-bit unsigned integer (0 to 18,446,744,073,709,551,615) */
typedef unsigned long long uint64;

/** @} */ // end of unsigned_types

/**
 * @defgroup signed_types Signed Integer Types
 * @{
 */

/** 8-bit signed integer (-128 to 127) */
typedef signed char sint8;

/** 16-bit signed integer (-32,768 to 32,767) */
typedef signed short sint16;

/** 32-bit signed integer (-2,147,483,648 to 2,147,483,647) */
typedef signed int sint32;

/** 64-bit signed integer (-9,223,372,036,854,775,808 to 9,223,372,036,854,775,807) */
typedef signed long long sint64;

/** @} */ // end of signed_types

/**
 * @defgroup float_types Floating-Point Types
 * @{
 */

/** 32-bit single-precision floating point (IEEE 754) */
typedef float float32;

/** 64-bit double-precision floating point (IEEE 754) */
typedef double float64;

/** @} */ // end of float_types

#endif /* STD_TYPES_H */