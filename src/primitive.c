/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 00:19:26 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/24 04:08:46 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "primitive.h"
#include "mat4.h"
#include "ray.h"

t_ray transform_ray(t_mat4 transf, t_ray *in)
{
	t_ray ret;

	ret.pos = mat4_transform3(transf, in->pos);
	ret.dir = mat4_transform3(transf, in->dir);
	return ret;
}

int intersect(t_primitive *self, t_ray *from, t_hit_info *info)
{
	int res;
	t_ray from2;

	from2 = transform_ray(self->itransform, from);
	if ((res = self->intersect(self, &from2, info)))
	{
		mat4_transform3(self->transform, info->point);
		mat4_transform3(self->transform, info->normal);
	}
	return (res);
}

t_primitive *new_primitive(t_primitive *alloc, t_mat4 transform, t_vec3 diffuse)
{
	alloc->transform = transform;
	alloc->itransform = mat4_inverse(transform);
	alloc->diffuse = diffuse;
	/* TODO: creer matrice */
	return (alloc);
}
