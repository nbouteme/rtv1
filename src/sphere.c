/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:46:31 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/24 04:34:07 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"

#include "equation.h"
#include "vec3.h"
#include "ray.h"

int hitc = 0;

bool sphere_ray_intersect(t_primitive *base, t_ray *ray, t_vec3 out_point)
{
	t_sphere *self;
	t_vec3 l;
	float b;
	float c;
	float tmp;

	self = (void*)base;
	ft_memcpy(l, vec3_sub(ray->pos, base->pos), sizeof(t_vec3));
	b = 2 * vec3_dot(ray->dir, l);
	c = vec3_dot(l, l) - self->radius2;
	if (!solve_second(&(t_sec_equation){vec3_dot(ray->dir, ray->dir), b, c, &b, &c}))
		return (0);
	if (b > c)
	{
		tmp = b;
		b = c;
		c = tmp;
	}
	if (b < 0)
	{
		if (c < 0)
			return (0);
		b = c;
	}
	ft_memcpy(out_point, vec3_muls(ray->dir, b), sizeof(t_vec3));
	ft_memcpy(out_point, vec3_add(ray->pos, out_point), sizeof(t_vec3));
	hitc++;
	return (1);
}

t_primitive *new_sphere(t_sphere *ret, float radius, t_vec3 pos, int color)
{
	new_primitive(&ret->base, pos, color);
	ret->base.intersect = sphere_ray_intersect;
	ret->radius = radius;
	ret->radius2 = radius * radius;
	return ((t_primitive*)ret);
}
