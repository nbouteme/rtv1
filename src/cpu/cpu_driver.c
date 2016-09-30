/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_driver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 00:33:55 by nbouteme          #+#    #+#             */
/*   Updated: 2016/09/30 12:22:36 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <cpu/cpu.h>
#include <cpu/cpu_driver.h>

void print_vec3(t_vec3 *v)
{
	printf("{%f, %f, %f}\n", v->v[0], v->v[1], v->v[2]);
}

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
	t_vec3 lap;

	c->vphw = tan(M_PI / 8);
	c->vphh = (720.0f / 1280.0f) * c->vphw;
	lap = vec3_add(c->pos, c->dir);
	c->u = vec3_cross(c->up, c->dir);
	c->v = vec3_cross(c->dir, c->u);
	vec3_normalize(&c->u);
	vec3_normalize(&c->v);
	c->vpblp = vec3_sub(lap, vec3_sub(vec3_muls(c->v, c->vphh), vec3_muls(c->u, c->vphw)));
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
	specv = (t_vec3){{spec, spec, spec }};
	coef = coef < 0 ? 0.0 : coef;
	diff = vec3_muls(args->prim->diffuse, coef);
	return vec3_add(vec3_add(specv, diff), args->prim->ambiant);
}
t_vec3 color_from_ray(t_scene *scene, t_ray *from)
{
	int i = 0;
	t_hit_info hit[2];
	t_primitive *prim[2] = {0};
	t_vec3 out = {{0, 0, 0}};
	if (!intersect_with_smth(from, scene, &hit[0], &(t_inter_info){ 9999, &prim[0]}))
		return (vec3_null());
	while (i < scene->n_spots)
	{
		hit[1] = hit[0];
		prim[1] = prim[0];
		t_ray shadow_ray = gen_ray(vec3_add(hit[1].point, vec3_muls(hit[1].normal, 0.001f)), scene->spots[i].pos);
		t_vec3 light_dir = vec3_sub(scene->spots[i].pos, hit[1].point);
		if (intersect_with_smth(&shadow_ray, scene, &hit[1], &(t_inter_info){vec3_norme(light_dir), &prim[1]}))
			out = vec3_add(out, prim[0]->ambiant);
		else
			out = vec3_add(out, color_from_material(&(t_colargs) {
				scene, from, prim[0], &hit[1], shadow_ray, light_dir
		}));
		++i;
	}
	return vec3_muls(out, 1.0f / scene->n_spots);
}

void draw_scene(t_vec3 *surface, t_scene *scene)
{
	int x;
	int y;

	y = 0;
	bake_camray(&scene->cam);
	while (y < 720)
	{
		x = 0;
		while (x < 1280)
		{
			t_ray from_cam = gen_camray(x, y, &scene->cam);
			surface[(719 - y) * 1280 + x] = color_from_ray(scene, &from_cam);
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

int cpu_genimage(t_display *disp)
{
	static int done = 0;
	t_scene *scene;

	if (done)
		return 0;
	scene = generate_scene(disp->user_ptr);
	draw_scene(disp->disp_param, scene);
	correct_gamma(disp->disp_param);
	done = 1;
	free(scene->primitives);
	free(scene->spots);
	free(scene);
	return 0;
}
