/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_driver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 00:33:55 by nbouteme          #+#    #+#             */
/*   Updated: 2016/09/19 03:36:49 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <cpu/cpu.h>
#include <cpu/cpu_driver.h>
#include <pthread.h>

void draw_pscene(t_display *disp, t_scene *scene)
{
	int x;
	int y;
	t_vec3 *surface;

	surface = disp->disp_param;
	y = disp->renderer_driver->param.by;
	bake_camray(&scene->cam);
	while (y < disp->renderer_driver->param.y)
	{
		x = disp->renderer_driver->param.bx;
		while (x < disp->renderer_driver->param.x)
		{
			t_ray from_cam = gen_camray(x, y, &scene->cam);
			surface[(720 - y) * 1280 + x] = color_from_ray(scene, &from_cam);
			++x;
		}
		++y;
	}
}

typedef struct
{
	t_display *d;
	t_scene *s;
	int n;
} t_launch_param;

void start_draw(t_launch_param *params)
{
	t_display *d;
	t_display p;
	t_driver dr;
	
	d = params->d;
	p = *d;
	dr = *d->renderer_driver;
	dr.param.by = 720 / 4 * (long)params->n + 1;
	dr.param.y = 720 / 4 * ((long)params->n + 1) + 1;
	p.renderer_driver = &dr;
	draw_pscene(&p, params->s);
}

int mcpu_genimage(t_display *disp)
{
	static int done = 0;
	t_scene *scene;
	pthread_t th[3];
	t_launch_param lp[4];

	if (done)
		return 0;
	scene = generate_scene(disp->user_ptr);
	while (done < 3)
	{
		lp[done] = (t_launch_param ){disp, scene, done};
		pthread_create(&th[done], 0, (void*)start_draw, &lp[done]);
		++done;
	}
	lp[done] = (t_launch_param ){disp, scene, done};
	start_draw(&lp[done]);
	done = 0;
	while (done < 3)
		pthread_join(th[done++], 0);
	correct_gamma(disp->disp_param);
	free(scene->primitives);
	free(scene->spots);
	free(scene);
	return (0);
}
