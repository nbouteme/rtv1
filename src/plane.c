/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 01:05:12 by nbouteme          #+#    #+#             */
/*   Updated: 2016/08/05 01:57:57 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"
#include "vec3.h"
#include "mat4.h"
#include "ray.h"

bool plane_ray_intersect(t_primitive *base, t_ray *ray, t_hit_info *out)
{
	out->normal = (t_3dvec){0.0f, 1.0f, 0.0f};
	float demon = 1.0f / vec3_dot(out->normal, ray->dir);
	if (demon < 0)
		return false;
	float t = vec3_dot(vec3_sub(vec3_null(), ray->pos), out->normal) * demon;
	if (t < 0)
		return false;
	out->point = vec3_muls(ray->dir, t);
	return 1;
}

t_primitive *new_plane(t_plane *plane, t_mat4 trans, t_vec3 color)
{
	new_primitive(&ret->base, trans, color);
	ret->base.intersect = plane_ray_intersect;
	return ((t_primitive*)plane);
}
