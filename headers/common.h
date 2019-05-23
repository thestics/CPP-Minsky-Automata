#ifndef __COMMON_H__
#define _CRT_SECURE_NO_WARNINGS
#define __COMMON_H__
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <string.h>

typedef double DType; /* Double real type for application */

typedef int IType;    /* Integer type for application */

typedef unsigned NType; /* Unsigned type for application */

//TODO: v.b.: correct it with limits and float
#define EQ_EPS 0.000001 // epsilon : presision of arithmetics

#define MIN(a, b)       (a)<(b)?(a):(b)
#define MAX(a, b)       (a)>(b)?(a):(b)

#define  PD_EQL(a, b)   fabs((a)-(b)) < EQ_EPS


/* Point type as vector of two reals */
typedef struct DPoint_
{
	union  //classical and vector representation
	{
		struct
		{
			DType x;
			DType y;
		};
		DType ptr[2];
	};
} DPoint;


typedef struct DLine_
{
	DType a;
	DType b;
	DType c;
} DLine;

void* memzero(void* ptr, size_t n);
#endif