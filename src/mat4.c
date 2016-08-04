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

    int o = 2+(j-i);

    i += 4+o;
    j += 4-o;

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
