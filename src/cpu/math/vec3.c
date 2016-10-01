/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/23 04:45:22 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 13:06:37 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cpu/math.h>

float	vec3_norme(t_vec3 v)
{
	float n;

	n = vec3_dot(v, v);
	n = sqrtf(n);
	return (n);
}

t_vec3	mat_multv3(t_mat3 a, t_vec3 x)
{
	t_vec3	ret;
	int		i;
	int		j;

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

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3 ret;

	ret.v[0] = a.v[1] * b.v[2] - a.v[2] * b.v[1];
	ret.v[1] = a.v[2] * b.v[0] - a.v[0] * b.v[2];
	ret.v[2] = a.v[0] * b.v[1] - a.v[1] * b.v[0];
	return (ret);
}

void	vec3_normalize(t_vec3 *a)
{
	float n;

	n = vec3_norme(*a);
	a->v[0] /= n;
	a->v[1] /= n;
	a->v[2] /= n;
}

t_vec3	vec3_reflect(t_vec3 i, t_vec3 n)
{
	return (vec3_sub(i, vec3_muls(n, 2 * vec3_dot(n, i))));
}
