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
#include "mat4.h"
#include <stdio.h>
#include <unistd.h>

void cpu_init(t_driver *self)
{
	self->ctx = ft_memalloc(sizeof(t_cpudri_data));
	self->ctx->mlx_ptr = xmlx_init();
	self->ctx->win_ptr = xmlx_new_window(self->param.x, self->param.y,
										"rt", FLOAT);
	self->ctx->image = self->ctx->win_ptr->framebuffer;
	self->ctx->fb = (t_vec3*)self->ctx->image->buffer;
}

int intersect_with_smth(t_ray *from, t_scene *scene, t_hit_info *hit, t_primitive **out)
{
	int i;

	i = 0;
	while (i < scene->n_primitives)
	{
		if (intersect(scene->primitives[i], from, hit))
		{
			*out = scene->primitives[i];
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

	lap = vec3_add(pos, dir);
	u = vec3_cross(dir, (t_3dvec){0.0f, 1.0f, 0.0f});
	v = vec3_cross(u, dir);
	vec3_normalize(&u);
	vec3_normalize(&v);

	tmp1 = vec3_muls(v, viewPlaneHalfHeight);
	tmp2 = vec3_muls(u, viewPlaneHalfWidth);

	tmp3 = vec3_sub(tmp1, tmp2);
	viewPlaneBottomLeftPoint = vec3_sub(lap, tmp3);
	v = vec3_muls(v, viewPlaneHalfHeight * 2.0f / 720.0f);
	u = vec3_muls(u, viewPlaneHalfWidth * 2.0f / 1280.0f);
	tmp1 = vec3_muls(u, -x);
	tmp2 = vec3_muls(v, y);
	tmp3 = vec3_add(tmp2, tmp1);
	ppoint = vec3_add(viewPlaneBottomLeftPoint, tmp3);

	return (gen_ray(pos, ppoint));
}

t_ray gen_ray(t_vec3 from, t_vec3 to)
{
	t_ray ret;

	ret.dir = vec3_sub(to, from);
	vec3_normalize(&ret.dir);
	ret.pos = from;
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
				t_ray shadow_ray = gen_ray(vec3_add(hit.point, vec3_muls(hit.normal,
																		 0.00002f)),
										   mat4_transform3(prim->itransform, scene->spots[0].pos));
				if (!intersect_with_smth(&shadow_ray, scene, &hit, &prim))
				{
					t_vec3 diff;
					float coef = vec3_dot(hit.normal, shadow_ray.dir);
					coef = coef < 0 ? 0 : coef;
					diff = vec3_muls(prim->diffuse, coef);
					disp->renderer_driver->ctx->fb[y * 1280 + x] = diff;
				}
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
	scene = disp->user_ptr;
	while(1)
	{
		draw_scene(disp, scene);
		xmlx_present(self->ctx->win_ptr);
		scene->spots[0].pos.v[0]++;
	}
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
