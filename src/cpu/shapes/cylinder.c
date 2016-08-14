/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:46:31 by nbouteme          #+#    #+#             */
/*   Updated: 2016/08/14 03:07:15 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cpu/cpu.h>

bool cylinder_ray_intersect(t_primitive *base, t_ray *ray, t_hit_info *out)
{
	t_cylinder *self;

	self = (void*)base;

	float a, b, c;
	a = (ray->dir.s.x * ray->dir.s.x) + (ray->dir.s.y * ray->dir.s.y);
	b = 2 * ray->pos.s.x * ray->dir.s.x + 2 * ray->pos.s.y * ray->dir.s.y;
	c = (ray->pos.s.x * ray->pos.s.x) + (ray->pos.s.y * ray->pos.s.y) - 1;
	if (!solve_second(&(t_sec_equation){vec3_dot(ray->dir, ray->dir), b, c, &b, &c}))
		return (0);
	if (b < c)
		b = c;
	out->point = vec3_add(ray->pos, vec3_muls(ray->dir, b));
	out->normal = out->point;
	vec3_normalize(&out->normal);
	out->dist = b;
	return (1);
}

t_primitive *new_cylinder(t_cylinder *ret, t_mat4 trans, t_vec3 color)
{
	new_primitive(&ret->base, trans, color);
	ret->base.intersect = cylinder_ray_intersect;
	ret->radius = 1.0f;
	ret->radius2 = 1.0f;
	return ((t_primitive*)ret);
}
