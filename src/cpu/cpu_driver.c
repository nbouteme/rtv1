/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_driver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 00:33:55 by nbouteme          #+#    #+#             */
/*   Updated: 2016/08/14 04:16:32 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <cpu/cpu.h>
#include <cpu/cpu_driver.h>

void cpu_init(t_driver *self)
{
	self->ctx = ft_memalloc(sizeof(t_cpudri_data));
	self->ctx->mlx_ptr = xmlx_init();
	self->ctx->win_ptr = xmlx_new_window(self->param.x, self->param.y,
										"rt", FLOAT);
	self->ctx->image = self->ctx->win_ptr->framebuffer;
	self->ctx->fb = (t_vec3*)self->ctx->image->buffer;
}

typedef struct	s_inter_info
{
	float maxdist;
	t_primitive **out;
}				t_inter_info;

int intersect_with_smth(t_ray *from, t_scene *scene, t_hit_info *hit, t_inter_info *out)
{
	int i;
	bool hit_found;
	t_hit_info back;


	hit_found = false;
	i = 0;
	while (i < scene->n_primitives)
	{
		back = *hit;
		if (intersect(&scene->primitives[i], from, hit))
		{
			if (out->maxdist > hit->dist)
			{
				out->maxdist = hit->dist;
				hit_found = true;
				*out->out = &scene->primitives[i];
			}
			else
				*hit = back;
		}
		++i;
	}
	return (hit_found);
}

t_ray gen_ray(t_vec3 from, t_vec3 to);

t_ray gen_camray(int x, int y, t_vec3 pos, t_vec3 dir)
{
	t_vec3 u, v;
	t_vec3 viewPlaneBottomLeftPoint;
	float viewPlaneHalfWidth = tan(M_PI / 8);
	float viewPlaneHalfHeight = (720.0f / 1280.0f) * viewPlaneHalfWidth;

	dir = vec3_add(pos, dir);
	u = vec3_cross(dir, (t_3dvec){0.0f, 1.0f, 0.0f});
	v = vec3_cross(u, dir);
	vec3_normalize(&u);
	vec3_normalize(&v);
	viewPlaneBottomLeftPoint = vec3_sub(dir, vec3_sub(vec3_muls(v, viewPlaneHalfHeight), vec3_muls(u, viewPlaneHalfWidth)));
	v = vec3_muls(v, viewPlaneHalfHeight * 2.0f / 720.0f);
	u = vec3_muls(u, viewPlaneHalfWidth * 2.0f / 1280.0f);
	return (gen_ray(pos, vec3_add(viewPlaneBottomLeftPoint, vec3_add(vec3_muls(v, y), vec3_muls(u, -x)))));
}

t_ray gen_ray(t_vec3 from, t_vec3 to)
{
	t_ray ret;

	ret.dir = vec3_sub(to, from);
	vec3_normalize(&ret.dir);
	ret.pos = from;
	return (ret);
}
int max = 300;

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
			t_primitive *prim = 0;
			if (intersect_with_smth(&from_cam, scene, &hit, &(t_inter_info){ 500.0f, &prim}))
			{
				t_ray shadow_ray = gen_ray(vec3_add(hit.point, vec3_muls(hit.normal,
																		 0.5f)),
										   scene->spots[0].pos);
				if (!intersect_with_smth(&shadow_ray, scene, &hit,
&(t_inter_info){vec3_norme(vec3_sub(scene->spots[0].pos, hit.point)), &prim}))
				{
					t_vec3 diff;
					float coef = vec3_dot(hit.normal, shadow_ray.dir);
					coef = coef < 0 ? 0.0 : coef;
					diff = vec3_muls(prim->diffuse, coef);
					disp->renderer_driver->ctx->fb[y * 1280 + x] = diff;
				}
			}
			++x;
		}
		++y;
	}
}

float deg2rad(float deg);

extern float angle;

float conv(float c)
{
	if (c < 0.0031308f)
		return 12.92f * c;
	return (1.055f * powf(c, 0.4166667) - 0.055f);
}

void internal_draw(void *param)
{
	static int done = 0;
	t_driver *self;
	t_display *disp;
	t_scene *scene;

	self = ((void**)param)[0];
	disp = ((void**)param)[1];
	scene = generate_scene(disp->user_ptr);
	int pixs = 720 * 1280;
	int i;
	if (!done)
	{
		draw_scene(disp, scene);
		i = -1;
		while (++i < pixs)
			disp->renderer_driver->ctx->fb[i].s = (t_3dvec)
				{
					conv(disp->renderer_driver->ctx->fb[i].s.x),
					conv(disp->renderer_driver->ctx->fb[i].s.y),
					conv(disp->renderer_driver->ctx->fb[i].s.z)
				};
		done = 1;
		angle -= 10;
	}
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
