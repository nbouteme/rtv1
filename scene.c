/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:23:30 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/23 04:43:51 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "sphere.h"
#include "spot.h"

t_scene *load_scene(const char *fn)
{
	t_scene *ret;

	(void)fn;
	ret = ft_memalloc(sizeof(*ret));
	ret->n_primitives = 1;
	ret->n_spots = 1;
	ret->primitives = new_sphere(malloc(sizeof(t_sphere)), 1.0f,
								 (float[3]){ 0, 0, -10.0f }, 0x7f7f7f);
	ret->spots = new_spot(malloc(sizeof(*ret->spots)),
						(float[3]){ 10.0f, 10.0f, 0.0f });
	return (ret);
}
