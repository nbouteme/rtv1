/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:46:31 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/20 00:00:45 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"

bool sphere_ray_intersect(t_primitive *base, t_ray ray, t_vec3 *out_normal)
{
	t_sphere *self = (void*)base;
	return false;
}

t_primitive *new_sphere(float radius, t_vec3 pos)
{
	t_sphere *ret;

	ret = malloc(sizeof(*ret));
	new_primitive(&ret->base, pos);
	ret->base->intersect = sphere_ray_intersect;
	return ((t_primitive*)ret);
}
