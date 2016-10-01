/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:46:31 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 14:13:39 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cpu/cpu.h>

#define CROSS2D(a, b) ((a.s.x * b.s.x) + (a.s.y * b.s.y) - (a.s.z * b.s.z))

bool	cone_ray_intersect(t_primitive *base, t_ray *ray, t_hit_info *out)
{
	float a;
	float b;
	float c;

	a = CROSS2D(ray->dir, ray->dir);
	b = 2 * (CROSS2D(ray->pos, ray->dir));
	c = CROSS2D(ray->pos, ray->pos);
	if (!base || !solve_second(&(t_sec_equation){a, b, c, &b, &c}))
		return (0);
	if (b > c)
		ft_swap_any(&b, &c, sizeof(b));
	if (b <= 0.001f)
	{
		if (c <= 0.001f)
			return (0);
		b = c;
	}
	out->point = vec3_add(ray->pos, vec3_muls(ray->dir, b));
	out->normal = out->point;
	out->dist = b;
	a = 1.0f / sqrtf(2.0f);
	vec3_normalize(&out->normal);
	out->normal.s.z = out->normal.s.z > 0 ? -a : a;
	vec3_normalize(&out->normal);
	return (1);
}
