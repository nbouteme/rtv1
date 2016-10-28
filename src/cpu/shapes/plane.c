/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 01:05:12 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/28 02:34:48 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cpu/cpu.h>
#include <core/ray.h>

bool	plane_ray_intersect(t_primitive *base, t_ray *ray, t_hit_info *out)
{
	t_vec3	norm;
	float	t;

	(void)base;
	norm = (t_vec3){{0.0f, 0.0f, 1.0f}};
	if (ray->dir.s.z == 0.0f || ray->pos.s.z == 0)
		return (false);
	if ((ray->pos.s.z > 0 && ray->dir.s.z > 0)
		|| (ray->pos.s.z < 0 && ray->dir.s.z < 0))
		return (false);
	t = ray->pos.s.z / ray->dir.s.z;
	if (ray->pos.s.z < 0)
		norm.s.z = -1;
	t = t > 0 ? t : -t;
	out->point = vec3_add(ray->pos, vec3_muls(ray->dir, t));
	out->normal = norm;
	out->dist = t;
	return (true);
}
