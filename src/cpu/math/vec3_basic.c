/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_basic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 13:06:48 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 13:06:49 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cpu/math.h>

float	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.v[0] * b.v[0] + a.v[1] * b.v[1] + a.v[2] * b.v[2]);
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	t_vec3 r;

	r.v[0] = a.v[0] - b.v[0];
	r.v[1] = a.v[1] - b.v[1];
	r.v[2] = a.v[2] - b.v[2];
	return (r);
}

t_vec3	vec3_muls(t_vec3 v, float s)
{
	t_vec3 ret;

	ret.s = v.s;
	ret.v[0] *= s;
	ret.v[1] *= s;
	ret.v[2] *= s;
	return (ret);
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	t_vec3 ret;

	ret.s = a.s;
	ret.v[0] += b.v[0];
	ret.v[1] += b.v[1];
	ret.v[2] += b.v[2];
	return (ret);
}

t_vec3	vec3_null(void)
{
	t_vec3 ret;

	ft_memset(&ret.s, 0, sizeof(ret.s));
	return (ret);
}
