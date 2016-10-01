/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:46:31 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 14:13:45 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cpu/cpu.h>

bool	sphere_ray_intersect(t_primitive *base, t_ray *ray, t_hit_info *out)
{
	t_vec3	l;
	float	b;
	float	c;

	(void)base;
	l = ray->pos;
	b = 2 * vec3_dot(ray->dir, l);
	c = vec3_dot(l, l) - 1;
	if (!solve_second(&(t_sec_equation){vec3_dot(ray->dir, ray->dir)
					, b, c, &b, &c}))
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
	vec3_normalize(&out->normal);
	out->dist = b;
	return (1);
}
