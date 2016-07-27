/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/23 04:45:22 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/24 04:26:23 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float vec3_norme(t_vec3 v)
{
	float n;

	n = v[0] + v[1] + v[2];
	n = sqrtf(n);
	return (1.0f / n);
}

t_vec3 *mat_multv3(t_mat3 a, t_vec3 x)
{
	static t_vec3 ret;
	int i;
	int j;

	memset(ret, 0, sizeof(ret));
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			ret[j] += a[j][i] * x[i];
			++j;
		}
		++i;
	}
	return (&ret);
}

t_vec3 *vec3_sub(t_vec3 a, t_vec3 b)
{
	static t_vec3 r;

	r[0] = a[0] - b[0];
	r[1] = a[1] - b[1];
	r[2] = a[2] - b[2];
	return (&r);
}

float vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

t_vec3 *rotate_dir(float u, float v, t_vec3 dir)
{
	static t_vec3 ndir;
	t_vec3 tmp;
	static t_mat3 rotx;
	static t_mat3 roty;

	ft_memcpy(rotx[0], (float[3]){1.0f, 0.0f, 0.0f}, sizeof(float[3]));
	ft_memcpy(rotx[1], (float[3]){0.0f, cosf(u), -sinf(u)}, sizeof(float[3]));
	ft_memcpy(rotx[2], (float[3]){0.0f, sinf(u), cosf(u)}, sizeof(float[3]));
	ft_memcpy(roty[0], (float[3]){cosf(v), 0.0f, sinf(u)}, sizeof(float[3]));
	ft_memcpy(roty[1], (float[3]){0.0f, 1.0f, 0.0f}, sizeof(float[3]));
	ft_memcpy(roty[2], (float[3]){-sinf(v), 0.0f, cosf(u)}, sizeof(float[3]));
	ft_memcpy(tmp, *mat_multv3(rotx, dir), sizeof(t_vec3));
	ft_memcpy(ndir, *mat_multv3(roty, tmp), sizeof(t_vec3));
	return (&ndir);
}

t_vec3 *vec3_muls(t_vec3 v, float s)
{
	static t_vec3 ret;

	ft_memcpy(ret, v, sizeof(t_vec3));
	ret[0] *= s;
	ret[1] *= s;
	ret[2] *= s;
	return (&ret);
}

t_vec3 *vec3_add(t_vec3 a, t_vec3 b)
{
	static t_vec3 ret;

	ft_memcpy(ret, a, sizeof(t_vec3));
	ret[0] += b[0];
	ret[1] += b[1];
	ret[2] += b[2];
	return (&ret);
}
