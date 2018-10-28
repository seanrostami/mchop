#ifndef SJR_MCHOP
#define SJR_MCHOP


/* 
- truncates the mantissa of a floating-point value to a given number of binary places 
- example: running mchop(x,p) for x=+45.375 (binary:  101101.011) and p=9 should and does produce +45.375 (binary: +101101.011) 
- example: running mchop(x,p) for x=+45.375 (binary:  101101.011) and p=8 should and does produce +45.25  (binary: +101101.01 ) 
- example: running mchop(x,p) for x=-45.375 (binary: -101101.011) and p=3 should and does produce -40     (binary: -101000    ) 
- example: running mchop(x,p) for x=+45.375 (binary:  101101.011) and p=0 should and does produce  0      (binary:            ) 
- type-generic (supports double, float, long double) but this requires C11's _Generic feature 
- advantage: result is necessarily representable because truncation is accomplished by shifting radix point within mantissa and frexp/ldexp are used to manipulate the values 
- advantage: is faster and cleaner than a more naive implementation multiplying by powers with casts or converting to/from strings with format specifiers 
- disadvantage: cannot be used to truncate relative to a base that is not a power of 2 (e.g. decimal) 
- disadvantage: at this time, Complex numbers are not supported 
*/


#include <math.h>
/* Although <tgmath.h> offers type-generic frexp & ldexp, there is no type-generic modf (why not?) and I prefer to be explicit anyway. So, I use X, Xf, Xl for X=frexp, ldexp, modf as needed. */


/*******************************************************************************************/


/*
Type-Generic Call : mchop( x, p )
	Parameter x : a floating-point value, normal with respect to the appropriate type (this is not checked by mchop)
		Remark: at this time, the type of x may be double, float, and long double
	Parameter p : number of more-significant bits of x's mantissa to retain, with all less-significant bits set to 0
		Remark: it is the caller's responsibility to choose a sensible value for p, i.e. between 0 and the total length of x's binary mantissa
*/

double mchop( double x, int p );

#ifdef __STDC_VERSION__
#if __STDC_VERSION__ >= 199901L /* C99 check */
float mchopf( float x, int p );
#endif
#endif

#ifdef __STDC_VERSION__
#if __STDC_VERSION__ >= 199901L /* C99 check */
long double mchopl( long double x, int p );
#endif
#endif


/*******************************************************************************************/


double mchop( double x, int p ){
	int exponent;
	double mantissa = frexp( x, &exponent ); /* disassemble floating-point (the shifting below depends on the fact that frexp returns between 0 and 1) */
	double integral;
	modf( ldexp( mantissa, p ), &integral ); /* shift binary radix point right by p places and then ignore fractional part */
	mantissa = ldexp( integral, -p ); /* shift binary radix point left by p places */
	return ldexp( mantissa, exponent ); /* reassemble floating-point */
}

#ifdef __STDC_VERSION__
#if __STDC_VERSION__ >= 199901L /* C99 check */
float mchopf( float x, int p ){
	int exponent;
	float mantissa = frexpf( x, &exponent ); /* C99 */
	float integral;
	modff( ldexpf( mantissa, p ), &integral ); /* C99 */
	mantissa = ldexpf( integral, -p ); /* C99 */
	return ldexpf( mantissa, exponent ); /* C99 */
}
#endif
#endif

#ifdef __STDC_VERSION__
#if __STDC_VERSION__ >= 199901L /* C99 check */
long double mchopl( long double x, int p ){
	int exponent;
	long double mantissa = frexpl( x, &exponent ); /* C99 */
	long double integral;
	modfl( ldexpl( mantissa, p ), &integral ); /* C99 */
	mantissa = ldexpl( integral, -p ); /* C99 */
	return ldexpl( mantissa, exponent ); /* C99 */
}
#endif
#endif


#ifdef __STDC_VERSION__
#if __STDC_VERSION__ >= 201112L /* C11 check */
#define mchop(x,p) _Generic( (x), double:mchop, float:mchopf, long double:mchopl )(x,p) /* it is deliberate that there is no default association */
#endif
#endif


/*******************************************************************************************/


#endif /* SJR_MCHOP */
