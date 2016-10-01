/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_basic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 13:08:40 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 13:08:41 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cpu/math.h>

t_vec4	vec4_sub(t_vec4 a, t_vec4 b)
{
	t_vec4 r;

	r.v[0] = a.v[0] - b.v[0];
	r.v[1] = a.v[1] - b.v[1];
	r.v[2] = a.v[2] - b.v[2];
	r.v[3] = a.v[3] - b.v[3];
	return (r);
}

t_vec4	vec4_mul(t_vec4 a, t_vec4 b)
{
	t_vec4 r;

	r.v[0] = a.v[0] * b.v[0];
	r.v[1] = a.v[1] * b.v[1];
	r.v[2] = a.v[2] * b.v[2];
	r.v[3] = a.v[3] * b.v[3];
	return (r);
}

float	vec4_dot(t_vec4 a, t_vec4 b)
{
	return (a.v[0] * b.v[0]
			+ a.v[1] * b.v[1]
			+ a.v[2] * b.v[2]
			+ a.v[3] * b.v[3]);
}

t_vec4	vec4_muls(t_vec4 v, float s)
{
	t_vec4 ret;

	ret.s = v.s;
	ret.v[0] *= s;
	ret.v[1] *= s;
	ret.v[2] *= s;
	ret.v[3] *= s;
	return (ret);
}

t_vec4	vec4_add(t_vec4 a, t_vec4 b)
{
	t_vec4 ret;

	ret.s = a.s;
	ret.v[0] += b.v[0];
	ret.v[1] += b.v[1];
	ret.v[2] += b.v[2];
	ret.v[3] += b.v[3];
	return (ret);
}
