#ifndef MAT3_H
#define MAT3_H

#include <core/math_types/vec3.h>

struct	s_3dmat_named
{
	struct	s_3dvec a;
	struct	s_3dvec b;
	struct	s_3dvec c;
};

struct	s_3dmat
{
	union
	{
		struct	s_3dmat_named n;
		struct	s_3dvec v[3];
	};
};

typedef union
{
	struct s_3dmat s;
	float v[3][3];
}				t_mat3;

#endif
