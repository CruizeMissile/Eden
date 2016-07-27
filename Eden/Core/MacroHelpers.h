#pragma once

// Add a pointer by an integral offset (bytes)
#define EDN_PTR_ADD( PTR, OFFSET ) \
  ((char *)(PTR) + (OFFSET))

// Subtract a pointer by an integral offset (bytes)
#define EDN_PTR_SUB( PTR, OFFSET ) \
  ((char *)(PTR) - (OFFSET))

// Find the offset of a member within a class or struct
#define EDN_OFFSET_OF( TYPE, MEMBER ) \
  ((unsigned)(&((((TYPE *)NULL))->MEMBER)))

// Interal usage
#define EDN_STRINGIZE_2( _ ) #_
#define EDN_STRINGIZE( _ ) EDN_STRINGIZE_2( _ )

// Don't forget to use END_DISABLE
#define EDN_DISABLE_WARNING( WARN_ID ) \
  __pragma( warning( push ) ) \
  __pragma( warning( disable : WARN_ID ) )

// Disables a warning without the push call
#define EDN_PERM_DSIABLE_WARNING( WARN_ID ) \
  __pragma( warning( disable : WARN_ID ) )

#define EDN_END_DISABLE( ) \
  __pragma( warning( pop ) )

#define EDN_PASTE( _, __ )  _##__

// Convenient macro for getting the size in elements of a stack array
#define EDN_ElemCount( ARRAY ) \
  sizeof( ARRAY ) / sizeof( ARRAY[0] )

#define EDN_UNUSED( x ) \
  ((void)x)