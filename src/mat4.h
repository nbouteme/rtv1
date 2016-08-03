#ifndef MAT4_H
#define MAT4_H

#include "rtv1.h"

t_vec4 mat4_transform4(t_mat4 m, t_vec4 a);
t_vec3 mat4_transform3(t_mat4 m, t_vec3 a);
t_mat4 mat4_inverse(t_mat4 m);
t_mat4 mat4_translate(t_vec3 trans);

#endif
