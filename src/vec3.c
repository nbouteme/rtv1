/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/23 04:45:22 by nbouteme          #+#    #+#             */
/*   Updated: 2016/08/02 22:46:30 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "vec3.h"

float vec3_norme(t_vec3 v)
{
	float n;

	n = vec3_dot(v, v);
	n = sqrtf(n);
	return (n);
}

t_vec3 mat_multv3(t_mat3 a, t_vec3 x)
{
	t_vec3 ret;
	int i;
	int j;

	memset(ret.v, 0, sizeof(ret.v));
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			ret.v[j] += a.v[j][i] * x.v[i];
			++j;
		}
		++i;
	}
	return (ret);
}

t_vec3 vec3_sub(t_vec3 a, t_vec3 b)
{
	t_vec3 r;

	r.v[0] = a.v[0] - b.v[0];
	r.v[1] = a.v[1] - b.v[1];
	r.v[2] = a.v[2] - b.v[2];
	return (r);
}

float vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.v[0] * b.v[0] + a.v[1] * b.v[1] + a.v[2] * b.v[2]);
}

t_vec3 vec3_muls(t_vec3 v, float s)
{
	t_vec3 ret;

	ret.s = v.s;
	ret.v[0] *= s;
	ret.v[1] *= s;
	ret.v[2] *= s;
	return (ret);
}

t_vec3 vec3_add(t_vec3 a, t_vec3 b)
{
	t_vec3 ret;

	ret.s = a.s;
	ret.v[0] += b.v[0];
	ret.v[1] += b.v[1];
	ret.v[2] += b.v[2];
	return (ret);
}

t_vec3 vec3_div(t_vec3 a, t_vec3 b)
{
	t_vec3 ret;

	ret.s = a.s;
	ret.v[0] /= b.v[0];
	ret.v[1] /= b.v[1];
	ret.v[2] /= b.v[2];
	return (ret);
}

t_vec3 vec3_null()
{
	t_vec3 ret;

	ft_memset(&ret.s, 0, sizeof(ret.s));
	return (ret);
}

t_vec3 vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3 ret;

	ret.v[0] = a.v[1] * b.v[2] - a.v[2] * b.v[1];
	ret.v[1] = a.v[2] * b.v[0] - a.v[0] * b.v[2];
	ret.v[2] = a.v[0] * b.v[1] - a.v[1] * b.v[0];
	return (ret);
}

void vec3_normalize(t_vec3 *a)
{
	float n;

	n = vec3_norme(*a);
	a->v[0] /= n;
	a->v[1] /= n;
	a->v[2] /= n;
}
