/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:23:30 by nbouteme          #+#    #+#             */
/*   Updated: 2016/08/11 04:10:40 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "sphere.h"
#include "plane.h"
#include "cube.h"
#include "spot.h"
#include "mat4.h"
#include "mat3.h"

float deg2rad(float deg)
{
	const float tran = 180.0f / M_PI;

	return deg / tran;
}

extern float angle;

t_scene *load_scene(const char *fn)
{
	t_scene *ret;

	(void)fn;
	ret = ft_memalloc(sizeof(*ret));
	ret->n_primitives = 2;
	ret->n_spots = 1;
	ret->cam_dir.s = (t_3dvec){0.0f, 0.0f, 1.0f};
	ret->primitives = malloc(sizeof(t_primitive*) * 2);
	ret->primitives[0] = new_sphere(malloc(sizeof(t_sphere)), 1.0f,
									(t_3dvec){ 0, 0, 20.0f },
									(t_3dvec){0.5f, 0.5f, 0.5f});
	ret->primitives[1] = new_plane(malloc(sizeof(t_plane)),
								mat4_mult(
									mat4_translate((t_3dvec){0.0f, 0.0f, 30.0f }),
									mat4_rotation((t_3dvec){1.0f, 0.0f, 0.0f}, deg2rad(angle))
									),
								   (t_3dvec){0.0f, 0.5f, 0.5f});
	ret->spots = new_spot(malloc(sizeof(*ret->spots)),
						  (t_3dvec){ -5.0f, -5.0f, -5.0f });
	return (ret);
}
