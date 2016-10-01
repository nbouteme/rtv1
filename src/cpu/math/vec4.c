/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/23 04:45:22 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 13:08:29 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cpu/math.h>

float	vec4_norme(t_vec4 v)
{
	float n;

	n = vec4_dot(v, v);
	n = sqrtf(n);
	return (n);
}

t_vec4	mat_multv4(t_mat4 a, t_vec4 x)
{
	t_vec4	ret;
	int		i;
	int		j;

	ft_memset(ret.v, 0, sizeof(ret.v));
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

t_vec4	vec4_null(void)
{
	t_vec4 ret;

	ft_memset(&ret.s, 0, sizeof(ret.s));
	return (ret);
}

t_vec4	vec4_cross(t_vec4 a, t_vec4 b)
{
	t_vec4 ret;

	ret.v[0] = a.v[1] * b.v[2] - a.v[2] * b.v[1];
	ret.v[1] = a.v[2] * b.v[0] - a.v[0] * b.v[2];
	ret.v[2] = a.v[0] * b.v[1] - a.v[1] * b.v[0];
	return (ret);
}

void	vec4_normalize(t_vec4 *a)
{
	float n;

	n = vec4_norme(*a);
	a->v[0] /= n;
	a->v[1] /= n;
	a->v[2] /= n;
}
