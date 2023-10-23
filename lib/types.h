#pragma once

// BUILD_BUG_ON breaks the build if the given compile time condition
// is false.
#define BUILD_BUG_ON(condition) ((void)sizeof(char[1 - 2*!!(condition)]))

// Primitive fixed-width types.
typedef unsigned char u8;
typedef short i16;
typedef unsigned short u16;
typedef int i32;
typedef unsigned int u32;

// Typedefs to represent useful numerical concepts.
// size_t is used to represent memory ranges.
typedef u32 size_t;

// duration_t is used to represent durations, in mibiseconds
// (1/1024 of a second).
typedef u32 duration_t;

// Constants to help with data sizes.
// #define is used to make them integer width independent.

// B is bytes.
// #define B ((size_t) 1)

// KB is kilobytes.
#define KB ((size_t) 1024)

// MB is megabytes.
#define MB ((size_t) (1024 * 1024))

// Constants to help with times. Times are expressed in subdivisions of
// a second that are a power of two.

// MS is mibiseconds (1/1024 of a second).
#define MS ((duration_t) 1)

// S is seconds.
#define S ((duration_t) 1024)

#define NULL 0
