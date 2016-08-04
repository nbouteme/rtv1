#include "rtv1.h"
#include "mat3.h"

t_mat3 mat3_transpose(t_mat3 m)
{
	t_mat3 ret;
	unsigned i;
	unsigned j;

	i = ~0;
	while (++i < 3 && (j = ~0))
		while (++j < 3)
			ret.v[i][j] = m.v[j][i];
	return (ret);
}

float mat3_det(t_mat3 m)
{
	return (m.v[0][0] * (m.v[1][1] * m.v[2][2] - m.v[2][1] * m.v[1][2])
			- m.v[1][0] * (m.v[0][1] * m.v[2][2] - m.v[2][1] * m.v[0][2])
			+ m.v[2][0] * (m.v[0][1] * m.v[1][2] - m.v[1][1] * m.v[0][2]));

}

t_mat3 mat3_inverse(t_mat3 m)
{
	t_mat3 inv;
	float ood;

	ood = 1.0f / mat3_det(m);
	inv.v[0][0] = + (m.v[1][1] * m.v[2][2] - m.v[2][1] * m.v[1][2]) * ood;
	inv.v[1][0] = - (m.v[1][0] * m.v[2][2] - m.v[2][0] * m.v[1][2]) * ood;
	inv.v[2][0] = + (m.v[1][0] * m.v[2][1] - m.v[2][0] * m.v[1][1]) * ood;
	inv.v[0][1] = - (m.v[0][1] * m.v[2][2] - m.v[2][1] * m.v[0][2]) * ood;
	inv.v[1][1] = + (m.v[0][0] * m.v[2][2] - m.v[2][0] * m.v[0][2]) * ood;
	inv.v[2][1] = - (m.v[0][0] * m.v[2][1] - m.v[2][0] * m.v[0][1]) * ood;
	inv.v[0][2] = + (m.v[0][1] * m.v[1][2] - m.v[1][1] * m.v[0][2]) * ood;
	inv.v[1][2] = - (m.v[0][0] * m.v[1][2] - m.v[1][0] * m.v[0][2]) * ood;
	inv.v[2][2] = + (m.v[0][0] * m.v[1][1] - m.v[1][0] * m.v[0][1]) * ood;
	return (inv);
}

t_mat3 mat3_topleft(t_mat4 m)
{
	t_mat3 ret;
	unsigned i;

	i = ~0;
	while (++i < 3)
		ret.s.v[i] = (t_3dvec){m.v[i][0], m.v[i][1], m.v[i][2]};
	return (ret);
}

t_vec3 mat3_transform3(t_mat3 m, t_vec3 a)
{
	t_vec3 ret;
	unsigned i;
	unsigned j;

	ft_memset(&ret, 0, sizeof(ret));

	i = ~0;
	while (++i < 3 && (j = ~0))
		while (++j < 3)
				ret.v[i] += m.v[i][j] * a.v[j];
	return ret;
}
