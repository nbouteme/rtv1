/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 01:05:12 by nbouteme          #+#    #+#             */
/*   Updated: 2016/08/08 04:41:22 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"
#include "vec3.h"
#include "mat4.h"
#include "ray.h"

bool plane_ray_intersect(t_primitive *base, t_ray *ray, t_hit_info *out)
{
	t_vec3 plane_normal;

	(void)base;
	plane_normal.s = (t_3dvec){0.0f, 0.0f, 1.0f};
	float demon = 1.0f / vec3_dot(plane_normal, ray->dir);
	if (demon < 0)
		return false;
	float t = vec3_dot(vec3_sub(vec3_null(), ray->pos), plane_normal) * demon;
	if (t < 0)
		return false;
	out->point = vec3_muls(ray->dir, t);
	out->normal = plane_normal;
	out->dist = t;
	return 1;
}

t_primitive *new_plane(t_plane *ret, t_mat4 trans, t_vec3 color)
{
	new_primitive(&ret->base, trans, color);
	ret->base.intersect = plane_ray_intersect;
	return ((t_primitive*)ret);
}
