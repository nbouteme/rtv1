#ifndef MAT4_H
#define MAT4_H

#include "rtv1.h"

t_vec4 mat4_transform4(t_mat4 m, t_vec4 a);
t_vec3 mat4_transform3(t_mat4 m, t_vec3 a);
t_mat4 mat4_inverse(t_mat4 m);
t_mat4 mat4_translate(t_vec3 trans);
t_mat4 mat4_rotation(t_vec3 u, float t);
t_mat4	mat4_mult(t_mat4 a, t_mat4 b);
t_mat4	mat4_ident();
t_mat4	mat4_muls(t_mat4 a, float b);

#endif
