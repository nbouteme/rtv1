#ifndef CUBE_H
# define CUBE_H

#include "primitive.h"

typedef struct	s_cube
{
	t_primitive base;
	t_vec3 dims;
}				t_cube;

t_primitive *new_cube(t_cube *ret, t_mat4 trans, t_vec3 color);

#endif
