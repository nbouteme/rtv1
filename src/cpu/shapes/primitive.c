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

	from2 = transform_ray(self->itransform, self->inorm, from);
	res = self->intersect(self, &from2, info);
	if (res)
	{
		info->point = mat4_transform3(self->transform, info->point);
		info->normal = mat3_transform3(self->norm, info->normal);
	}
	return (res);
}

t_primitive *new_primitive(t_primitive *alloc, t_iprimitive *base)
{
	vec3_normalize(&base->trans.rot_axis);
	alloc->transform = mat4_mult(mat4_translate(base->trans.pos),
								 mat4_mult(mat4_rotation(base->trans.rot_axis,
														 base->trans.rot_angle),
									 mat4_ident()));
	alloc->itransform = mat4_inverse(alloc->transform);
	alloc->norm = mat3_transpose(mat3_topleft(alloc->transform));
	alloc->inorm = mat3_transpose(mat3_topleft(alloc->itransform));
	ft_memcpy(alloc->diffuse.v, base->mat.diffuse, sizeof(t_vec3));
	return (alloc);
}
