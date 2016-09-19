/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:46:31 by nbouteme          #+#    #+#             */
/*   Updated: 2016/09/19 03:33:06 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cpu/cpu.h>

bool cone_ray_intersect(t_primitive *base, t_ray *ray, t_hit_info *out)
{
	(void)base;
	float a, b, c;
	a = (ray->dir.s.x * ray->dir.s.x) + (ray->dir.s.y * ray->dir.s.y) - (ray->dir.s.z * ray->dir.s.z);
	b = 2 * (ray->pos.s.x * ray->dir.s.x + ray->pos.s.y * ray->dir.s.y - ray->pos.s.z * ray->dir.s.z);
	c = (ray->pos.s.x * ray->pos.s.x) + (ray->pos.s.y * ray->pos.s.y) - (ray->pos.s.z * ray->pos.s.z);
	if (!solve_second(&(t_sec_equation){a, b, c, &b, &c}))
		return (0);
	if (b > c)
	{
		a = b;
		b = c;
		c = a;
	}
	if (b <= 0.001f)
	{
		if (c <= 0.001f)
			return (0);
		b = c;
	}
	out->point = vec3_add(ray->pos, vec3_muls(ray->dir, b));
	a = 1.0f / sqrtf(2.0f);
	/* TODO: Compute the correct normal  */
	out->normal = out->point;
	vec3_normalize(&out->normal);
	out->normal.s.z = out->normal.s.z > 0 ? -a : a;
	vec3_normalize(&out->normal);
	out->dist = b;
	return (1);
}
