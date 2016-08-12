#ifndef CUBE_H
# define CUBE_H

#include "primitive.h"

typedef struct	s_cube
{
	t_primitive base;
	t_vec3 dims;
}				t_cube;

bool cube_ray_intersect(t_primitive *base, t_ray *ray, t_hit_info *out);
t_primitive *new_cube(t_cube *ret, t_vec3 dims, t_vec3 pos, t_vec3 color);


#endif
