/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:46:31 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/23 04:43:14 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"

bool sphere_ray_intersect(t_primitive *base, t_ray *ray, t_vec3 out_normal)
{
	t_sphere *self = (void*)base;
	(void)ray;
	(void)out_normal;
	(void)self;
	return false;
}

t_primitive *new_sphere(t_sphere *ret, float radius, t_vec3 pos, int color)
{
	new_primitive(&ret->base, pos, color);
	ret->base.intersect = sphere_ray_intersect;
	ret->radius = radius;
	return ((t_primitive*)ret);
}
