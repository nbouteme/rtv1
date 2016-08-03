/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_driver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 00:33:55 by nbouteme          #+#    #+#             */
/*   Updated: 2016/08/02 23:31:09 by nbouteme         ###   ########.fr       */
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

int intersect_with_smth(t_ray *from, t_scene *scene, t_hit_info *hit, t_primitive **out)
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

t_ray gen_ray(t_vec3 from, t_vec3 to);

t_ray gen_camray(int x, int y, t_vec3 pos, t_vec3 dir)
{
	t_vec3 u, v, tmp1, tmp2, tmp3;
	t_vec3 viewPlaneBottomLeftPoint, lap;
	t_vec3 ppoint;
	float viewPlaneHalfWidth = tan(M_PI / 8);
	float aspectRatio = 720.0f / 1280.0f;
	float viewPlaneHalfHeight = aspectRatio * viewPlaneHalfWidth;

	ft_memcpy(lap, vec3_add(pos, dir), sizeof(t_vec3));
	ft_memcpy(u, vec3_cross(dir, (float[]){0.0f, 1.0f, 0.0f}), sizeof(t_vec3));
	ft_memcpy(v, vec3_cross(u, dir), sizeof(t_vec3));
	vec3_normalize(u);
	vec3_normalize(v);

	ft_memcpy(tmp1, vec3_muls(v, viewPlaneHalfHeight), sizeof(t_vec3));
	ft_memcpy(tmp2, vec3_muls(u, viewPlaneHalfWidth), sizeof(t_vec3));

	ft_memcpy(tmp3, vec3_sub(tmp1, tmp2), sizeof(t_vec3));
	ft_memcpy(viewPlaneBottomLeftPoint, vec3_sub(lap, tmp3), sizeof(t_vec3));
	ft_memcpy(v, vec3_muls(v, viewPlaneHalfHeight * 2.0f / 720.0f), sizeof(t_vec3));
	ft_memcpy(u, vec3_muls(u, viewPlaneHalfWidth * 2.0f / 1280.0f), sizeof(t_vec3));
	ft_memcpy(tmp1, vec3_muls(u, -x), sizeof(t_vec3));
	ft_memcpy(tmp2, vec3_muls(v, y), sizeof(t_vec3));
	ft_memcpy(tmp3, vec3_add(tmp2, tmp1), sizeof(t_vec3));
	ft_memcpy(ppoint, vec3_add(viewPlaneBottomLeftPoint, tmp3), sizeof(t_vec3));

	return (gen_ray(pos, ppoint));
}

t_ray gen_ray(t_vec3 from, t_vec3 to)
{
	t_ray ret;

	ft_memcpy(ret.dir, vec3_sub(to, from), sizeof(t_vec3));
	vec3_normalize(ret.dir);
	ft_memcpy(ret.pos, from, sizeof(t_vec3));
	return (ret);
}

void draw_scene(t_display *disp, t_scene *scene)
{
	int x;
	int y;

	y = 0;
	while (y < disp->renderer_driver->param.y)
	{
		x = 0;
		while (x < disp->renderer_driver->param.x)
		{
			t_ray from_cam = gen_camray(x, y, scene->cam_pos, scene->cam_dir);
			t_hit_info hit;
			t_primitive *prim;
			if (intersect_with_smth(&from_cam, scene, &hit, &prim))
			{
				t_ray shadow_ray = gen_ray(*(t_vec3*)vec3_add(hit.point,
													*(t_vec3*)vec3_muls(hit.normal,
															  0.001f)),
										scene->spots[0].pos);
				if (!intersect_with_smth(&shadow_ray, scene, &hit, &prim))
					disp->renderer_driver->ctx->fb[y * 1280 + x] = prim->diffuse;
				else
					disp->renderer_driver->ctx->fb[y * 1280 + x] = 0x303030;
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
