#include <cpu/math.h>

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

t_mat3 mat3_ident()
{
	t_mat3 ret;
	unsigned i;

	ft_memset(&ret, 0, sizeof(ret));
	i = ~0;
	while (++i < 3)
			ret.v[i][i] = 1.0f;
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

t_mat3	mat3_mult(t_mat3 a, t_mat3 b)
{
	t_mat3	c;
	int		i;
	int		j;
	int		k;

	i = 0;
	ft_memset(&c, 0, sizeof(c));
	while (i < 3)
	{
		k = 0;
		while (k < 3)
		{
			j = 0;
			while (j < 3)
			{
				c.v[i][j] += a.v[i][k] * b.v[k][j];
				++j;
			}
			++k;
		}
		++i;
	}
	return (c);
}

t_mat3	mat3_muls(t_mat3 a, float b)
{
	int		i;
	int		j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			a.v[i][j] *= b;
			++j;
		}
		++i;
	}
	return (a);
}

t_mat3	mat3_add(t_mat3 a, t_mat3 b)
{
	int		i;
	int		j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			a.v[i][j] += b.v[i][j];
			++j;
		}
		++i;
	}
	return (a);
}
