#include "mat4.h"

t_vec4 mat4_transform4(t_mat4 m, t_vec4 a)
{
	t_vec4 ret;
	unsigned i;
	unsigned j;

	ft_memset(&ret, 0, sizeof(ret));

	i = ~0;
	while (++i < 4 && (j = ~0))
		while (++j < 4)
				ret.v[i] += m.v[j][i] * a.v[j];
	return ret;
}

t_vec3 mat4_transform3(t_mat4 m, t_vec3 a)
{
	t_vec4 ret;

	ret = mat4_transform4(m, (t_4dvec){
				a.v[0],
				a.v[1],
				a.v[2],
				1.0f});
	return (t_vec3){
		(t_3dvec){ret.v[0], ret.v[1], ret.v[2]}
	};
}
