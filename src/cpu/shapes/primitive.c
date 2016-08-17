/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 00:19:26 by nbouteme          #+#    #+#             */
/*   Updated: 2016/08/11 03:56:56 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cpu/cpu.h>

t_ray transform_ray(t_mat4 transf, t_mat3 norm, t_ray *in)
{
	t_ray ret;

	ret.pos = mat4_transform3(transf, in->pos);
	ret.dir = mat3_transform3(norm, in->dir);
	return ret;
}

int intersect(t_primitive *self, t_ray *from, t_hit_info *info)
{
	t_ray from2;
	int res;

	/* FIXME: Incohérences dans l'utilisation des inverses  */
	from2 = transform_ray(self->itransform, self->norm, from);
	res = self->intersect(self, &from2, info);
	if (res)
	{
		info->point = mat4_transform3(self->transform, info->point);
		info->normal = mat3_transform3(self->inorm, info->normal);
	}
	return (res);
}

t_primitive *new_primitive(t_primitive *alloc, t_mat4 transform, t_vec3 diffuse)
{
	alloc->transform = transform;
	alloc->itransform = mat4_inverse(transform);
	alloc->norm = mat3_transpose(mat3_topleft(alloc->transform));
	alloc->inorm = mat3_transpose(mat3_topleft(alloc->itransform));
	alloc->diffuse = diffuse;
	/* TODO: creer matrice */
	return (alloc);
}
