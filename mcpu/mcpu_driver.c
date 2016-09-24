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

void mcpu_init(t_driver *self)
{
	self->ctx = ft_memalloc(sizeof(t_cpudri_data));
	self->ctx->mlx_ptr = xmlx_init();
	self->ctx->win_ptr = xmlx_new_window(self->param.x, self->param.y,
										"rt", FLOAT);
	self->ctx->win_ptr->on_key = handle_key;
	self->ctx->image = self->ctx->win_ptr->framebuffer;
	self->ctx->fb = (t_vec3*)self->ctx->image->buffer;
}

void draw_pscene(t_display *disp, t_scene *scene)
{
	int x;
	int y;

	y = disp->renderer_driver->param.by;
	bake_camray(&scene->cam);
	while (y < disp->renderer_driver->param.y)
	{
		x = disp->renderer_driver->param.bx;
		while (x < disp->renderer_driver->param.x)
		{
			t_ray from_cam = gen_camray(x, y, &scene->cam);
			disp->renderer_driver->ctx->fb[(720 - y) * 1280 + x] = color_from_ray(scene, &from_cam);
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
	dr.param.by = 720 / 4 * (long)params->n;
	dr.param.y = 720 / 4 * ((long)params->n + 1);
	p.renderer_driver = &dr;
	draw_pscene(&p, params->s);
}

void internal_pdraw(void *param)
{
	static int done = 0;
	t_driver *self;
	t_display *disp;
	t_scene *scene;
	pthread_t th[3];
	t_launch_param lp[4];

	self = ((void**)param)[0];
	disp = ((void**)param)[1];
	if (!done)
	{
		scene = generate_scene(disp->user_ptr);
		while (done < 3)
		{
			lp[done] = (t_launch_param ){disp, scene, done};
			pthread_create(&th[done], 0, (void*)start_draw, &lp[done]);
			++done;
		}
		puts("Finished creating threads");
		lp[done] = (t_launch_param ){disp, scene, done};
		start_draw(&lp[done]);
		//draw_pscene(disp, scene);
		done = 0;
		correct_gamma(disp->renderer_driver->ctx->fb);
		done = 1;
		free(scene->primitives);
		free(scene->spots);
		free(scene);
	}
	xmlx_present(self->ctx->win_ptr);
}

void mcpu_genimage(t_driver *self, t_display *disp)
{
	t_cpudri_data *data;

	data = self->ctx;
	xmlx_run_window(data->win_ptr, internal_pdraw, &(void *[]){self, disp});
}

void mcpu_destroy(t_driver *self)
{
	(void) self;
}
