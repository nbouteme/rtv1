/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:23:30 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/19 23:24:11 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_scene *load_scene(const char *fn)
{
	t_scene *ret;

	(void)fn;
	ret = malloc(sizeof(*ret));
	ret->n_primitives = 1;
	ret->n_spots = 1;
	ret->primitives = new_sphere(1.0f, (float[3]){ 0, 0, -10.0f });
	ret->spots = new_spot((float[3]){ 10.0f, 10.0f, 0.0f });
	ret->cam_pos = malloc(3 * sizeof(float));
	ret->cam_dir = malloc(3 * sizeof(float));
}
