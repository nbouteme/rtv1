#include "mat4.h"
#include "mat3.h"

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
/*
float invf(int i, int j, t_mat4 *m)
{
    int o;
    int u;
    int n;
    int k;
    int l;

	o = 2 + (j - i);
    i += 4 + o;
    j += 4 - o;
	u = j + 1;
	n = j - 1;
	k = i - 1;
	l = 1 + 1;
    return (((o % 2) ? 1 : -1) *
			(m->v[n % 4][l % 4] * m->v[j % 4][i % 4] * m->v[u % 4][k % 4]
			 + m->v[u % 4][l % 4] * m->v[n % 4][i % 4] * m->v[j % 4][k % 4]
			 + m->v[n % 4][k % 4] * m->v[j % 4][l % 4] * m->v[u % 4][i % 4]
			 - m->v[n % 4][k % 4] * m->v[j % 4][i % 4] * m->v[u % 4][l % 4]
			 - m->v[u % 4][k % 4] * m->v[n % 4][i % 4] * m->v[j % 4][l % 4]
			 - m->v[n % 4][l % 4] * m->v[j % 4][k % 4] * m->v[u % 4][i % 4]));
			 }*/

float invf(int i, int j, t_mat4 *m)
{

    int o = 2 + (j - i);

    i += 4 + o;
    j += 4 - o;

    #define e(a,b) m->v[(j + b) % 4][(i + a) % 4]

    float inv =
     + e(+1, -1) * e(+0, +0) * e(-1, +1)
     + e(+1, +1) * e(+0, -1) * e(-1, +0)
     + e(-1, -1) * e(+1, +0) * e(+0, +1)
     - e(-1, -1) * e(+0, +0) * e(+1, +1)
     - e(-1, +1) * e(+0, -1) * e(+1, +0)
     - e(+1, -1) * e(-1, +0) * e(+0, +1);

    return (o % 2) ? inv : -inv;
    #undef e
}

t_mat4 mat4_inverse(t_mat4 m)
{
    t_mat4 inv;
	unsigned i;
	unsigned j;
    float det;

	i = ~0;
    while (++i < 4 && (j = ~0))
		while (++j < 4)
            inv.v[i][j] = invf(j, i, &m);
    det = m.v[0][0];
	i = 0;
    while (++i < 4)
		det *= m.v[i][i];
	det = 1.0f / det;
	i = ~0;
    while (++i < 4 && (j = ~0))
		while (++j < 4)
			inv.v[i][j] *= det;
    return (inv);
}

t_mat4 mat4_rotation(t_vec3 u, float t)
{
	t_mat3 p;
	t_mat3 q;
	t_mat3 r;
	t_mat4 o;
	t_mat3 i;

	i = mat3_ident();
	p.s.v[0] = (t_3dvec){u.s.x * u.s.x, u.s.x * u.s.y, u.s.x * u.s.z };
	p.s.v[1] = (t_3dvec){u.s.x * u.s.y, u.s.y * u.s.y, u.s.y * u.s.z };
	p.s.v[2] = (t_3dvec){u.s.x * u.s.z, u.s.z * u.s.y, u.s.z * u.s.z };
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
	unsigned j;

	ft_memset(&ret, 0, sizeof(ret));
	i = ~0;
	while (++i < 4 && (j = ~0))
		while (++j < 4)
			ret.v[i][j] = 1.0f;
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
