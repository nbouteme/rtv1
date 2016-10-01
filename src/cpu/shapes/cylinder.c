/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:46:31 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 14:14:05 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cpu/cpu.h>

bool	cylinder_ray_intersect(t_primitive *base, t_ray *ray, t_hit_info *out)
{
	float a;
	float b;
	float c;

	(void)base;
	a = (ray->dir.s.x * ray->dir.s.x) + (ray->dir.s.y * ray->dir.s.y);
	b = 2 * ray->pos.s.x * ray->dir.s.x + 2 * ray->pos.s.y * ray->dir.s.y;
	c = (ray->pos.s.x * ray->pos.s.x) + (ray->pos.s.y * ray->pos.s.y) - 1;
	if (!solve_second(&(t_sec_equation){a, b, c, &b, &c}))
		return (0);
	if (b > c)
		ft_swap_any(&b, &c, sizeof(b));
	if (b < 0)
	{
		if (c < 0)
			return (0);
		b = c;
	}
	out->point = vec3_add(ray->pos, vec3_muls(ray->dir, b));
	out->normal = out->point;
	out->normal.s.z = 0;
	out->dist = b;
	return (1);
}
