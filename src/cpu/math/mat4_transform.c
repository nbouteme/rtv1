/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 12:47:33 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 13:04:08 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cpu/math.h>

t_vec4	mat4_transform4(t_mat4 m, t_vec4 a)
{
	t_vec4		ret;
	unsigned	i;
	unsigned	j;

	ft_memset(&ret, 0, sizeof(ret));
	i = ~0;
	while (++i < 4 && (j = ~0))
		while (++j < 4)
			ret.v[i] += m.v[i][j] * a.v[j];
	return (ret);
}

t_vec3	mat4_transform3(t_mat4 m, t_vec3 a)
{
	t_vec4 ret;

	ret = mat4_transform4(m, (t_4dvec){
				a.v[0],
				a.v[1],
				a.v[2],
				1.0f
	});
	return (t_vec3){
		(t_3dvec){
			ret.v[0] / ret.v[3],
			ret.v[1] / ret.v[3],
			ret.v[2] / ret.v[3]
		}
	};
}

t_mat4	mat4_rotation(t_vec3 u, float t)
{
	t_mat3 q;
	t_mat3 r;
	t_mat4 o;
	t_mat3 i;

	i = mat3_ident();
	q.s.v[0] = (t_3dvec){0, -u.s.z, u.s.y};
	q.s.v[1] = (t_3dvec){u.s.z, 0, -u.s.x};
	q.s.v[2] = (t_3dvec){-u.s.y, u.s.x, 0};
	r = mat3_add(i, mat3_add(mat3_muls(q, sinf(t)),
							mat3_muls(mat3_mult(q, q), 1 - cosf(t))));
	o.s.v[0] = (t_4dvec){r.v[0][0], r.v[0][1], r.v[0][2], 0.0f};
	o.s.v[1] = (t_4dvec){r.v[1][0], r.v[1][1], r.v[1][2], 0.0f};
	o.s.v[2] = (t_4dvec){r.v[2][0], r.v[2][1], r.v[2][2], 0.0f};
	o.s.v[3] = (t_4dvec){0.0f, 0.0f, 0.0f, 1.0f};
	return (o);
}

t_mat4	mat4_translate(t_vec3 pos)
{
	t_mat4 ret;

	ret.s.v[0] = (t_4dvec){1.0f, 0.0f, 0.0f, pos.v[0]};
	ret.s.v[1] = (t_4dvec){0.0f, 1.0f, 0.0f, pos.v[1]};
	ret.s.v[2] = (t_4dvec){0.0f, 0.0f, 1.0f, pos.v[2]};
	ret.s.v[3] = (t_4dvec){0.0f, 0.0f, 0.0f, 1.0f};
	return (ret);
}
