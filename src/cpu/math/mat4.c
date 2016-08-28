#include <cpu/math.h>

t_vec4 mat4_transform4(t_mat4 m, t_vec4 a)
{
	t_vec4 ret;
	unsigned i;
	unsigned j;

	ft_memset(&ret, 0, sizeof(ret));

	i = ~0;
	while (++i < 4 && (j = ~0))
		while (++j < 4)
				ret.v[i] += m.v[i][j] * a.v[j];
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

t_mat4 mat4_translate(t_vec3 pos)
{
	t_mat4 ret;

	ret.s.v[0] = (t_4dvec){1.0f, 0.0f, 0.0f, pos.v[0]};
	ret.s.v[1] = (t_4dvec){0.0f, 1.0f, 0.0f, pos.v[1]};
	ret.s.v[2] = (t_4dvec){0.0f, 0.0f, 1.0f, pos.v[2]};
	ret.s.v[3] = (t_4dvec){0.0f, 0.0f, 0.0f, 1.0f};
	return (ret);
}

void mat_invcoef(t_mat4 m, float coefs[])
{
	coefs[ 0] = m.v[2][2] * m.v[3][3] - m.v[3][2] * m.v[2][3];
	coefs[ 1] = m.v[1][2] * m.v[3][3] - m.v[3][2] * m.v[1][3];
	coefs[ 2] = m.v[1][2] * m.v[2][3] - m.v[2][2] * m.v[1][3];
	coefs[ 3] = m.v[2][1] * m.v[3][3] - m.v[3][1] * m.v[2][3];
	coefs[ 4] = m.v[1][1] * m.v[3][3] - m.v[3][1] * m.v[1][3];
	coefs[ 5] = m.v[1][1] * m.v[2][3] - m.v[2][1] * m.v[1][3];
	coefs[ 6] = m.v[2][1] * m.v[3][2] - m.v[3][1] * m.v[2][2];
	coefs[ 7] = m.v[1][1] * m.v[3][2] - m.v[3][1] * m.v[1][2];
	coefs[ 8] = m.v[1][1] * m.v[2][2] - m.v[2][1] * m.v[1][2];
	coefs[ 9] = m.v[2][0] * m.v[3][3] - m.v[3][0] * m.v[2][3];
	coefs[10] = m.v[1][0] * m.v[3][3] - m.v[3][0] * m.v[1][3];
	coefs[11] = m.v[1][0] * m.v[2][3] - m.v[2][0] * m.v[1][3];
	coefs[12] = m.v[2][0] * m.v[3][2] - m.v[3][0] * m.v[2][2];
	coefs[13] = m.v[1][0] * m.v[3][2] - m.v[3][0] * m.v[1][2];
	coefs[14] = m.v[1][0] * m.v[2][2] - m.v[2][0] * m.v[1][2];
	coefs[15] = m.v[2][0] * m.v[3][1] - m.v[3][0] * m.v[2][1];
	coefs[16] = m.v[1][0] * m.v[3][1] - m.v[3][0] * m.v[1][1];
	coefs[17] = m.v[1][0] * m.v[2][1] - m.v[2][0] * m.v[1][1];
}

t_mat4 mat4_inverse(t_mat4 m)
{
	int i;
	float coefs[18];
	t_vec4 faces[6];
	t_vec4 vec[4];
	t_vec4 inv[4];
	t_vec4 sign[2];
	t_mat4 inverse;
	t_vec4 dot;
	t_vec4 row;

	mat_invcoef(m, coefs);
	i = 0;
	while (i < 6)
	{
		faces[i].s = (t_4dvec){ coefs[i * 3], coefs[i * 3], coefs[i * 3 + 1], coefs[i * 3 + 2] };
		++i;
	}
	i = 0;
	while (i < 4)
	{
		vec[i].s = (t_4dvec){ m.v[1][i], m.v[0][i], m.v[0][i], m.v[0][i] };
		++i;
	}
	inv[0] = vec4_add(vec4_sub(vec4_mul(vec[1], faces[0]), vec4_mul(vec[2], faces[1])), vec4_mul(vec[3], faces[2]));
	inv[1] = vec4_add(vec4_sub(vec4_mul(vec[0], faces[0]), vec4_mul(vec[2], faces[3])), vec4_mul(vec[3], faces[4]));
	inv[2] = vec4_add(vec4_sub(vec4_mul(vec[0], faces[1]), vec4_mul(vec[1], faces[3])), vec4_mul(vec[3], faces[5]));
	inv[3] = vec4_add(vec4_sub(vec4_mul(vec[0], faces[2]), vec4_mul(vec[1], faces[4])), vec4_mul(vec[2], faces[5]));
	sign[0].s = (t_4dvec){+1, -1, +1, -1};
	sign[1].s = (t_4dvec){-1, +1, -1, +1};
	i = 0;
	while (i < 4)
	{
		inverse.s.v[i] = vec4_mul(inv[i], sign[i % 2]).s;
		row.v[i] = inv[i].v[0];
		++i;
	}
	dot = vec4_mul(m.s.v[0], row);
	float det = dot.s.x + dot.s.y + dot.s.z + dot.s.w;
	return (mat4_muls(inverse, 1.0f / det));
}

t_mat4 mat4_rotation(t_vec3 u, float t)
{
	t_mat3 q;
	t_mat3 r;
	t_mat4 o;
	t_mat3 i;

	i = mat3_ident();
	q.s.v[0] = (t_3dvec){0, -u.s.z, u.s.y};
	q.s.v[1] = (t_3dvec){u.s.z, 0, -u.s.x};
	q.s.v[2] = (t_3dvec){-u.s.y, u.s.x, 0};
	r = mat3_add(i, mat3_add(mat3_muls(q, sinf(t)), mat3_muls(mat3_mult(q, q), 1 - cosf(t))));
	o.s.v[0] = (t_4dvec){r.v[0][0], r.v[0][1], r.v[0][2], 0.0f};
	o.s.v[1] = (t_4dvec){r.v[1][0], r.v[1][1], r.v[1][2], 0.0f};
	o.s.v[2] = (t_4dvec){r.v[2][0], r.v[2][1], r.v[2][2], 0.0f};
	o.s.v[3] = (t_4dvec){0.0f, 0.0f, 0.0f, 1.0f};
	return (o);
}

t_mat4 mat4_ident()
{
	t_mat4 ret;
	unsigned i;

	ft_memset(&ret, 0, sizeof(ret));
	i = ~0;
	while (++i < 4)
			ret.v[i][i] = 1.0f;
	return (ret);
}

t_mat4	mat4_mult(t_mat4 a, t_mat4 b)
{
	t_mat4	c;
	int		i;
	int		j;
	int		k;

	i = 0;
	ft_memset(&c, 0, sizeof(c));
	while (i < 4)
	{
		k = 0;
		while (k < 4)
		{
			j = 0;
			while (j < 4)
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

t_mat4	mat4_muls(t_mat4 a, float b)
{
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			a.v[i][j] *= b;
			++j;
		}
		++i;
	}
	return (a);
}
