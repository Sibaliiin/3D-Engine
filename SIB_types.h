#ifndef	SIB_TYPES_H
#define	SIB_TYPES_H

// 3 dimensional vector
typedef struct
{
	float x;
	float y;
	float z;
} vec3;

typedef struct
{
	vec3 p1;
	vec3 p2;
	vec3 p3;
} triangle;

#endif
