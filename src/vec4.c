/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/23 04:45:22 by nbouteme          #+#    #+#             */
/*   Updated: 2016/08/10 02:40:30 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "vec4.h"

float vec4_norme(t_vec4 v)
{
	float n;

	n = vec4_dot(v, v);
	n = sqrtf(n);
	return (n);
}

t_vec4 mat_multv4(t_mat4 a, t_vec4 x)
{
	t_vec4 ret;
	int i;
	int j;

	memset(ret.v, 0, sizeof(ret.v));
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			ret.v[j] += a.v[j][i] * x.v[i];
			++j;
		}
		++i;
	}
	return (ret);
}

t_vec4 vec4_sub(t_vec4 a, t_vec4 b)
{
	t_vec4 r;

	r.v[0] = a.v[0] - b.v[0];
	r.v[1] = a.v[1] - b.v[1];
	r.v[2] = a.v[2] - b.v[2];
	r.v[3] = a.v[3] - b.v[3];
	return (r);
}

t_vec4 vec4_mul(t_vec4 a, t_vec4 b)
{
	t_vec4 r;

	r.v[0] = a.v[0] * b.v[0];
	r.v[1] = a.v[1] * b.v[1];
	r.v[2] = a.v[2] * b.v[2];
	r.v[3] = a.v[3] * b.v[3];
	return (r);
}

float vec4_dot(t_vec4 a, t_vec4 b)
{
	return (a.v[0] * b.v[0] + a.v[1] * b.v[1] + a.v[2] * b.v[2] + a.v[3] * b.v[3]);
}

t_vec4 vec4_muls(t_vec4 v, float s)
{
	t_vec4 ret;

	ret.s = v.s;
	ret.v[0] *= s;
	ret.v[1] *= s;
	ret.v[2] *= s;
	ret.v[3] *= s;
	return (ret);
}

t_vec4 vec4_add(t_vec4 a, t_vec4 b)
{
	t_vec4 ret;

	ret.s = a.s;
	ret.v[0] += b.v[0];
	ret.v[1] += b.v[1];
	ret.v[2] += b.v[2];
	ret.v[3] += b.v[3];
	return (ret);
}

t_vec4 vec4_div(t_vec4 a, t_vec4 b)
{
	t_vec4 ret;

	ret.s = a.s;
	ret.v[0] /= b.v[0];
	ret.v[1] /= b.v[1];
	ret.v[2] /= b.v[2];
	ret.v[3] /= b.v[3];
	return (ret);
}

t_vec4 vec4_null()
{
	t_vec4 ret;

	ft_memset(&ret.s, 0, sizeof(ret.s));
	return (ret);
}

t_vec4 vec4_cross(t_vec4 a, t_vec4 b)
{
	t_vec4 ret;

	ret.v[0] = a.v[1] * b.v[2] - a.v[2] * b.v[1];
	ret.v[1] = a.v[2] * b.v[0] - a.v[0] * b.v[2];
	ret.v[2] = a.v[0] * b.v[1] - a.v[1] * b.v[0];
	return (ret);
}

void vec4_normalize(t_vec4 *a)
{
	float n;

	n = vec4_norme(*a);
	a->v[0] /= n;
	a->v[1] /= n;
	a->v[2] /= n;
}
