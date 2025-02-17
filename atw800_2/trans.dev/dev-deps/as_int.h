#ifndef AS_INT_TYPES_H
#define AS_INT_TYPES_H 1

typedef unsigned int     uint32_t;
typedef signed int       int32_t;
typedef signed short     int16_t;
typedef unsigned short   uint16_t;
typedef unsigned char    uint8_t;
typedef signed char      int8_t;
typedef signed char      bool;

#ifndef false
#define false 0
#endif

#ifndef true
#define true 1
#endif 

#ifndef NULL
#define NULL 0
#endif


#define RIGHT_SHIFT_IS_UNSIGNED 1
#ifdef RIGHT_SHIFT_IS_UNSIGNED
#define SHIFT_TEMPS	int shift_temp;
/* ersetzt durch Variante von Mike Bruestle
#define RIGHT_SHIFT(x,shft)  \
	((shift_temp = (x)) < 0 ? \
	 (shift_temp >> (shft)) | ((~((INT32) 0)) << (32-(shft))) : \
	 (shift_temp >> (shft)))
*/
#define RIGHT_SHIFT(x,shft)  \
    ((shift_temp = (x)) < 0 ? \
    ~(~shift_temp >> (shft)) : \
    (shift_temp >> (shft)))

#else
#define SHIFT_TEMPS
#define RIGHT_SHIFT(x,shft)	((x) >> (shft))
#endif


#endif

