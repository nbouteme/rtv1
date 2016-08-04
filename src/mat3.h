#ifndef MAT3_H
#define MAT3_H


t_mat3 mat3_transpose(t_mat3 m);
float mat3_det(t_mat3 m);
t_mat3 mat3_inverse(t_mat3 m);
t_mat3 mat3_topleft(t_mat4 m);
t_vec3 mat3_transform3(t_mat3 m, t_vec3 a);


#endif
