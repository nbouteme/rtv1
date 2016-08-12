#ifndef MAT4_H
#define MAT4_H

#include <core/math_types/vec4.h>

struct	s_4dmat_named
{
	struct	s_4dvec a;
	struct	s_4dvec b;
	struct	s_4dvec c;
	struct	s_4dvec d;
};

struct	s_4dmat
{
	union
	{
		struct	s_4dmat_named n;
		struct	s_4dvec v[4];
	};
};

typedef union
{
	struct s_4dmat s;
	float v[4][4];
}				t_mat4;

#endif
