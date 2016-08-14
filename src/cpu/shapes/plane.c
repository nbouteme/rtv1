/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 01:05:12 by nbouteme          #+#    #+#             */
/*   Updated: 2016/08/11 04:05:59 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cpu/cpu.h>
#include <core/ray.h>

bool plane_ray_intersect(t_primitive *base, t_ray *ray, t_hit_info *out)
{
	t_plane *self;

	self = (t_plane *)base;
	float demon = vec3_dot(self->normal, ray->dir);
	if (demon >= 0)
		return false;
	float t = vec3_dot(vec3_sub(vec3_null(), ray->pos), self->normal) / demon;
	if (t < 0)
		return false;
	out->point = vec3_add(ray->pos, vec3_muls(ray->dir, t));
	out->normal = self->normal;
	out->dist = t;
	return 1;
}

t_primitive *new_plane(t_plane *ret, t_mat4 trans, t_vec3 color)
{
	new_primitive(&ret->base, trans, color);
	ret->base.intersect = plane_ray_intersect;
	ret->normal.s = (t_3dvec){0.0f, 0.0f, -1.0f};
	return ((t_primitive*)ret);
}
