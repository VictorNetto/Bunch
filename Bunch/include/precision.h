#pragma once

#include <float.h>
#include <math.h>

/*
Bunch can be build with single or double precision.
To handle this we define the type real that is float
or double and, in the same spirit, the real_functions
(e.g. real_sin, real_exp etc).
*/

namespace bunch {

#if 1
	typedef float real;
	#define real_sqrt sqrtf
	#define real_abs fabsf
	#define real_sin sinf
	#define real_cos cosf
	#define real_exp expf
	#define real_pow powf
	#define PI 3.14159f
#else
	typedef double real;
	#define real_sqrt sqrt
	#define real_abs fabs
	#define real_sin sin
	#define real_cos cos
	#define real_exp exp
	#define real_pow pow
	#define PI 3.14159265358979
#endif

}