/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_driver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 00:33:55 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/24 05:17:46 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "int_cpu_driver.h"
#include "display.h"
#include "ray.h"
#include "scene.h"
#include "vec3.h"
#include "clear_mlx.h"
#include <unistd.h>

void cpu_init(t_driver *self)
{
	self->ctx = ft_memalloc(sizeof(t_cpudri_data));
	self->ctx->mlx_ptr = mlx_init();
	self->ctx->win_ptr = mlx_new_window(self->ctx->mlx_ptr,
								self->param.x, self->param.y, "rt");
	self->ctx->image = mlx_new_image(self->ctx->mlx_ptr, 1280, 720);
	self->ctx->fb = (int*)self->ctx->image->buffer;
}

int intersect_with_smth(t_ray *from, t_scene *scene, t_vec3 hit, t_primitive **out)
{
	int i;

	i = 0;
	while (i < scene->n_primitives)
	{
		if (scene->primitives[i].intersect(&scene->primitives[i],
										   from, hit))
		{
			*out = &scene->primitives[i];
			return (1);
		}
		++i;
	}
	return (0);
}

t_ray gen_camray(int x, int y, t_vec3 pos, t_vec3 dir)
{
	const float hquantum = (1280.0f / 90.0f);
	const float vquantum = (720.0f / 50.0f);
	t_ray ret;
	float xrot;
	float yrot;

	ft_memcpy(ret.pos, pos, sizeof(t_vec3));
	xrot = ((x - 640) * hquantum) / 90.0f;
	yrot = ((y - 360) * vquantum) / 50.0f;
	ft_memcpy(ret.dir, rotate_dir(xrot, yrot, dir), sizeof(t_vec3));
	return (ret);
}

t_ray gen_ray(t_vec3 from, t_vec3 to)
{
	float n;
	t_ray ret;

	ret.pos[0] = to[0] - from[0];
	ret.pos[1] = to[1] - from[1];
	ret.pos[2] = to[2] - from[2];
	n = vec3_norme(ret.pos);
	ret.pos[0] *= n;
	ret.pos[1] *= n;
	ret.pos[2] *= n;
	return (ret);
}

void draw_scene(t_display *disp, t_scene *scene)
{
	int x;
	int y;
	int i;

	y = 0;
	while (y < disp->renderer_driver->param.y)
	{
		x = 0;
		while (x < disp->renderer_driver->param.x)
		{
			t_ray from_cam = gen_camray(x, y, scene->cam_pos, scene->cam_dir);
			t_vec3 hit;
			i = 0;
			t_primitive *prim;
			if (intersect_with_smth(&from_cam, scene, hit, &prim))
			{
				t_ray shadow_ray = gen_ray(hit, scene->spots[0].pos);
				if (!intersect_with_smth(&shadow_ray, scene, hit, &prim))
					disp->renderer_driver->ctx->fb[y * 1280 + x] = 0x00FFFFFFu;
			}
			++x;
		}
		++y;
	}
}

int internal_draw(void *param)
{
	t_driver *self;
	t_display *disp;
	t_scene *scene;
	extern int hitc;

	self = ((void**)param)[0];
	disp = ((void**)param)[1];
	scene = disp->user_ptr;
	draw_scene(disp, scene);
	mlx_put_image_to_window(self->ctx->mlx_ptr, self->ctx->win_ptr, self->ctx->image, 0, 0);
	mlx_do_sync(self->ctx->mlx_ptr);
	read(0, &hitc, 1);
	end_application();
	return (0);
}

void cpu_genimage(t_driver *self, t_display *disp)
{
	t_cpudri_data *data;

	data = self->ctx;
	(void)disp;
	mlx_loop_hook(data->mlx_ptr, internal_draw, &(void *[]){self, disp});
	mlx_loop(data->mlx_ptr);
}

void cpu_destroy(t_driver *self)
{
	(void) self;
}
