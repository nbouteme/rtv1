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

typedef struct	s_colargs
{
	t_scene *scene;
	t_ray *ray;
	t_primitive *prim;
	t_hit_info *hit;
	t_ray shadow_ray;
	t_vec3 light_dir;
}				t_colargs;

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

void bake_camray(t_camera *c)
{
	c->vphw = tan(M_PI / 8);
	c->vphh = (720.0f / 1280.0f) * c->vphw;
	c->dir = vec3_add(c->pos, c->dir);
	c->u = vec3_cross(c->dir, c->up);
	c->v = vec3_cross(c->u, c->dir);
	vec3_normalize(&c->u);
	vec3_normalize(&c->v);
	c->vpblp = vec3_sub(c->dir, vec3_sub(vec3_muls(c->v, c->vphh), vec3_muls(c->u, c->vphw)));
	c->v = vec3_muls(c->v, c->vphh * 2.0f / 720.0f);
	c->u = vec3_muls(c->u, c->vphw * 2.0f / 1280.0f);
}

t_ray gen_camray(int x, int y, t_camera *c)
{
	return (gen_ray(c->pos, vec3_add(c->vpblp, vec3_add(vec3_muls(c->v, y),
														vec3_muls(c->u, -x)))));
}

t_ray gen_ray(t_vec3 from, t_vec3 to)
{
	t_ray ret;

	ret.dir = vec3_sub(to, from);
	vec3_normalize(&ret.dir);
	ret.pos = from;
	return (ret);
}

float maxf(float a, float b)
{
	return a < b ? b : a;
}

t_vec3 color_from_material(t_colargs *args)
{
	t_vec3 diff;
	float coef;
	t_vec3 refl;
	float spec;
	t_vec3 specv;

	coef = vec3_dot(args->hit->normal, args->shadow_ray.dir);
	refl = vec3_reflect(args->light_dir, args->hit->normal);
	vec3_normalize(&refl);
	spec = powf(maxf(vec3_dot(args->ray->dir, refl), 0.0), args->prim->spec);
	specv = (t_vec3){{spec / 2, spec / 2, spec / 2 }};
	coef = coef < 0 ? 0.0 : coef;
	diff = vec3_muls(args->prim->diffuse, coef);
	return vec3_add(vec3_add(specv, diff), args->prim->ambiant);
}

t_vec3 color_from_ray(t_scene *scene, t_ray *from)
{
	t_hit_info hit;
	t_primitive *prim = 0;
	if (!intersect_with_smth(from, scene, &hit, &(t_inter_info){ 9999, &prim}))
		return (vec3_null());
	t_ray shadow_ray = gen_ray(vec3_add(hit.point, vec3_muls(hit.normal, 0.001f)), scene->spots[0].pos);
	t_vec3 light_dir = vec3_sub(scene->spots[0].pos, hit.point);
	if (intersect_with_smth(&shadow_ray, scene, &hit, &(t_inter_info){vec3_norme(light_dir), &prim}))
		return prim->ambiant;
	return color_from_material(&(t_colargs){
			scene, from, prim, &hit, shadow_ray, light_dir
		});
}

void draw_scene(t_display *disp, t_scene *scene)
{
	int x;
	int y;

	y = 0;
	bake_camray(&scene->cam);
	while (y < disp->renderer_driver->param.y)
	{
		x = 0;
		while (x < disp->renderer_driver->param.x)
		{
			if (x == 666 && y == 360)
				puts("");
			t_ray from_cam = gen_camray(x, y, &scene->cam);
			disp->renderer_driver->ctx->fb[y * 1280 + x] = color_from_ray(scene, &from_cam);
			++x;
		}
		++y;
	}
}

float deg2rad(float deg);

float conv(float c)
{
	if (c < 0.0031308f)
		return 12.92f * c;
	return (1.055f * powf(c, 0.4166667) - 0.055f);
}

void correct_gamma(t_vec3 *framebuffer)
{
	const int pixs = 720 * 1280;
	int i;

	i = -1;
	while (++i < pixs)
		framebuffer[i].s = (t_3dvec)
			{
				conv(framebuffer[i].s.x),
				conv(framebuffer[i].s.y),
				conv(framebuffer[i].s.z)
			};
}

void internal_draw(void *param)
{
	static int done = 0;
	t_driver *self;
	t_display *disp;
	t_scene *scene;

	self = ((void**)param)[0];
	disp = ((void**)param)[1];
	if (!done)
	{
		scene = generate_scene(disp->user_ptr);
		draw_scene(disp, scene);
		correct_gamma(disp->renderer_driver->ctx->fb);
		done = 1;
		free(scene->primitives);
		free(scene->spots);
		free(scene);
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
