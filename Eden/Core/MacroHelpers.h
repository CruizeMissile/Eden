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

#define H1(s,i,x)   (x*65599u+(uint8_t)s[(i)<strlen(s)?strlen(s)-1-(i):strlen(s)])
#define H4(s,i,x)   H1(s,i,H1(s,i+1,H1(s,i+2,H1(s,i+3,x))))
#define H16(s,i,x)  H4(s,i,H4(s,i+4,H4(s,i+8,H4(s,i+12,x))))
#define H64(s,i,x)  H16(s,i,H16(s,i+16,H16(s,i+32,H16(s,i+48,x))))
#define H256(s,i,x) H64(s,i,H64(s,i+64,H64(s,i+128,H64(s,i+192,x))))

#define EDN_HASH(s)    ((uint32_t)(H256(s,0,0)^(H256(s,0,0)>>16)))