/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:23:30 by nbouteme          #+#    #+#             */
/*   Updated: 2016/08/14 03:46:50 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cpu/cpu.h>
#include <core/iscene.h>

float deg2rad(float deg)
{
	const float tran = 180.0f / M_PI;

	return deg / tran;
}

extern float angle;


#define I2(a, b) a ## b
#define I(x) I2(x, _ray_intersect)

t_scene *generate_scene(t_iscene *fn)
{
	const t_ray_intersect_fun funs[] = {I(plane), I(sphere),
										I(cone), I(cylinder)};
	t_scene *ret;
	int i;

	i = 0;
	ret = ft_memalloc(sizeof(*ret));
	ft_memcpy(ret->cam.dir.v, fn->cam_dir, sizeof(t_vec3));
	ft_memcpy(ret->cam.pos.v, fn->cam_pos, sizeof(t_vec3));
	ft_memcpy(ret->cam.up.v, fn->cam_up, sizeof(t_vec3));
	ret->n_primitives = fn->n_primitives;
	ret->n_spots = fn->n_spots;
	ret->spots = ft_memcpy(malloc(sizeof(t_spot) * fn->n_spots), fn->spots,
						sizeof(t_spot) * fn->n_spots);
	ret->primitives = malloc(sizeof(t_primitive) * fn->n_primitives);
	while (i < fn->n_primitives)
	{
		new_primitive(&ret->primitives[i], &fn->primitives[i]);
		ret->primitives[i].intersect = funs[fn->primitives[i].type];
		++i;
	}
	return (ret);
}
