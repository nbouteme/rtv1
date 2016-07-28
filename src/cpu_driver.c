/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_driver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 00:33:55 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/28 04:11:40 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "int_cpu_driver.h"
#include "display.h"
#include "ray.h"
#include "scene.h"
#include "vec3.h"
#include <stdio.h>
#include <unistd.h>

void cpu_init(t_driver *self)
{
	self->ctx = ft_memalloc(sizeof(t_cpudri_data));
	self->ctx->mlx_ptr = xmlx_init();
	self->ctx->win_ptr = xmlx_new_window(self->param.x, self->param.y,
										"rt", INTEGER);
	self->ctx->image = self->ctx->win_ptr->framebuffer;
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
	const float hquantum = ((M_PI / 2.0f) / 1280.0f);
	const float vquantum = (0.872665f / 720.0f);
	t_ray ret;
	float xrot;
	float yrot;

	ft_memcpy(ret.pos, pos, sizeof(t_vec3));
	ft_memcpy(ret.dir, dir, sizeof(t_vec3));
	xrot = (x - 640) * hquantum;
	yrot = (y - 360) * vquantum;

	ret.dir[1] = cosf(xrot) * ret.dir[1] + sinf(xrot) * ret.dir[2];
	ret.dir[2] = cosf(xrot) * ret.dir[1] + sinf(xrot) * ret.dir[2];

	ret.dir[0] = cosf(xrot) * ret.dir[0] - sinf(xrot) * ret.dir[2];
	ret.dir[2] = cosf(xrot) * ret.dir[0] - sinf(xrot) * ret.dir[2];

	float n = vec3_norme(ret.dir);
	ret.dir[0] /= n;
	ret.dir[1] /= n;
	ret.dir[2] /= n;
	return (ret);
}

t_ray gen_ray(t_vec3 from, t_vec3 to)
{
	float n;
	t_ray ret;

	ret.dir[0] = to[0] - from[0];
	ret.dir[1] = to[1] - from[1];
	ret.dir[2] = to[2] - from[2];
	n = vec3_norme(ret.dir);
	ret.dir[0] /= n;
	ret.dir[1] /= n;
	ret.dir[2] /= n;
	ft_memcpy(ret.pos, from, sizeof(t_vec3));
	return (ret);
}

void draw_scene(t_display *disp, t_scene *scene)
{
	int x;
	int y;
	int i;
	int a, b;
	t_ray from_cam;

	a = 0;
	b = 0;
	from_cam = gen_camray(a, b, scene->cam_pos, scene->cam_dir);
	printf("(%d, %d) => (%.3f, %.3f, %.3f)\n",
		   a, b, from_cam.dir[0], from_cam.dir[1], from_cam.dir[2]);

	a = 1280;
	b = 0;
	from_cam = gen_camray(a, b, scene->cam_pos, scene->cam_dir);
	printf("(%d, %d) => (%.3f, %.3f, %.3f)\n",
		   a, b, from_cam.dir[0], from_cam.dir[1], from_cam.dir[2]);

	a = 0;
	b = 720;
	from_cam = gen_camray(a, b, scene->cam_pos, scene->cam_dir);
	printf("(%d, %d) => (%.3f, %.3f, %.3f)\n",
		   a, b, from_cam.dir[0], from_cam.dir[1], from_cam.dir[2]);

	a = 1280;
	b = 720;
	from_cam = gen_camray(a, b, scene->cam_pos, scene->cam_dir);
	printf("(%d, %d) => (%.3f, %.3f, %.3f)\n",
		   a, b, from_cam.dir[0], from_cam.dir[1], from_cam.dir[2]);
	exit(1);

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

void internal_draw(void *param)
{
	t_driver *self;
	t_display *disp;
	t_scene *scene;
	extern int hitc;

	self = ((void**)param)[0];
	disp = ((void**)param)[1];
	disp->renderer_driver->ctx->fb[0] = 0x00FFFFFFu;
	scene = disp->user_ptr;
	draw_scene(disp, scene);
	xmlx_present(self->ctx->win_ptr);
}

void cpu_genimage(t_driver *self, t_display *disp)
{
	t_cpudri_data *data;

	data = self->ctx;
	xmlx_run_window(data->win_ptr, internal_draw, &(void *[]){self, disp});
}

void cpu_destroy(t_driver *self)
{
	(void) self;
}
