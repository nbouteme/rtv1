/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_driver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 00:33:55 by nbouteme          #+#    #+#             */
/*   Updated: 2017/01/30 14:56:17 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

void	draw_scene(t_vec3 *surface, t_scene *scene)
{
	int		x;
	int		y;
	t_ray	from_cam;

	y = 0;
	bake_camray(&scene->cam);
	while (y < 720)
	{
		x = 0;
		while (x < 1280)
		{
			from_cam = gen_camray(x, y, &scene->cam);
			surface[(719 - y) * 1280 + x] = color_from_ray(scene, &from_cam, 0);
			++x;
		}
		++y;
	}
}

int		cpu_genimage(t_display *disp)
{
	static int	done = 0;
	t_scene		*scene;

	if (done)
		return (0);
	scene = generate_scene(disp->user_ptr);
	draw_scene(disp->disp_param, scene);
	correct_gamma(disp->disp_param);
	done = 1;
	free(scene->primitives);
	free(scene->spots);
	free(scene);
	return (0);
}
