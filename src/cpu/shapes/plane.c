/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 01:05:12 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 13:31:54 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cpu/cpu.h>
#include <core/ray.h>

bool	plane_ray_intersect(t_primitive *base, t_ray *ray, t_hit_info *out)
{
	const t_vec3	norm = {{0.0f, 0.0f, -1.0f}};
	float			demon;
	float			t;

	demon = vec3_dot(norm, ray->dir);
	(void)base;
	if (demon >= 0)
		return (false);
	t = vec3_dot(vec3_sub(vec3_null(), ray->pos), norm) / demon;
	if (t < 0)
		return (false);
	out->point = vec3_add(ray->pos, vec3_muls(ray->dir, t));
	out->normal = norm;
	out->dist = t;
	return (true);
}
