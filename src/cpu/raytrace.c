/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 12:42:37 by nbouteme          #+#    #+#             */
/*   Updated: 2017/02/09 02:53:14 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

#define MAXF(a, b) (a < b ? b : a)

int		inter(t_ray *from, t_scene *scene, t_hit_info *hit, t_inter_info *out)
{
	int			i;
	int			hit_found;
	t_hit_info	back;

	hit_found = 0;
	i = 0;
	while (i < scene->n_primitives)
	{
		back = *hit;
		if (intersect(&scene->primitives[i], from, hit))
		{
			if (out->maxdist > hit->dist)
			{
				out->maxdist = hit->dist;
				hit_found = 1;
				*out->out = &scene->primitives[i];
			}
			else
				*hit = back;
		}
		++i;
	}
	return (hit_found);
}

t_vec3 vec3_refract(t_vec3 a, t_vec3 n, float r)
{
	float k;

	k = 1.0f - r * r * (1.0f - vec3_dot(n, a) * vec3_dot(n, a));
	if (k < 0.0f)
		return vec3_null();
	return vec3_sub(vec3_muls(a, r), vec3_muls(n, (r * vec3_dot(n, a) + sqrtf(k))));
}

t_vec3	color_from_material(t_colargs *args)
{
	t_vec3	diff;
	float	coef;
	t_vec3	refl;
	float	spec;
	t_vec3	specv;

	coef = vec3_dot(args->hit->normal, args->shadow_ray.dir);
	refl = vec3_reflect(args->light_dir, args->hit->normal);
	vec3_normalize(&refl);
	if (args->prim->mat.reflectivity == 1.0f)
		return (color_from_ray(args->scene, &(t_ray){vec3_add(args->hit->point, vec3_muls(vec3_reflect(args->ray->dir, args->hit->normal), 0.001f)),
						vec3_reflect(args->ray->dir, args->hit->normal)}, args->depth + 1));
	if (args->prim->mat.transluscence == 1.0f)
		return (color_from_ray(args->scene, &(t_ray){vec3_add(args->hit->point, vec3_muls(vec3_reflect(args->ray->dir, args->hit->normal), 0.001f)),
						args->ray->dir}, args->depth + 1));
	spec = pow(MAXF(vec3_dot(args->ray->dir, refl), 0.0f), args->prim->mat.spec_intensity);
	specv = (t_vec3){{spec, spec, spec }};
	diff = vec3_muls(args->prim->mat.diffuse, coef < 0 ? 0.0f : coef);
	specv = vec3_add(vec3_add(specv, diff), args->prim->mat.ambiant);
	if (args->prim->mat.reflectivity < 1.0f && args->prim->mat.reflectivity > 0)
		specv = vec3_mix(specv, color_from_ray(args->scene, &(t_ray){vec3_add(args->hit->point, vec3_muls(vec3_reflect(args->ray->dir, args->hit->normal), 0.001f)),
		vec3_reflect(args->ray->dir, args->hit->normal)}, args->depth + 1), args->prim->mat.reflectivity);
	if (args->prim->mat.transluscence < 1.0f && args->prim->mat.transluscence > 0)
		specv = vec3_mix(specv, color_from_ray(args->scene, &(t_ray){vec3_add(args->hit->point, vec3_muls(vec3_reflect(args->ray->dir, args->hit->normal), 0.001f)),
		vec3_reflect(args->ray->dir, args->hit->normal)}, args->depth + 1), args->prim->mat.reflectivity);
	return (specv);
}

typedef t_inter_info	t_ii;

t_vec3	color_from_ray(t_scene *s, t_ray *from, int depth)
{
	int			i;
	t_hit_info	h[2];
	t_primitive	*p[2];
	t_ray		r;
	t_vec3		out[2];

	i = -1;
	if (depth >= MAX_DEPTH || !inter(from, s, &h[0], &(t_inter_info){9999, &p[0]}))
		return (vec3_null());
	ft_memset(&out[1], 0, sizeof(out[1]));
	while (++i < s->n_spots)
	{
		h[1] = h[0];
		p[1] = p[0];
		r = gen_ray(vec3_add(h[1].point,
			vec3_muls(h[1].normal, 0.001f)), s->spots[i].pos);
		out[0] = vec3_sub(s->spots[i].pos, h[1].point);
		if (inter(&r, s, &h[1], &(t_ii){vec3_norme(out[0]), &p[1]}))
			out[1] = vec3_add(out[1], p[0]->mat.ambiant);
		else
			out[1] = vec3_add(out[1], color_from_material(&(t_colargs) {
						s, from, p[0], &h[1], r, out[0], depth}));
	}
	return (vec3_muls(out[1], 1.0f / s->n_spots));
}
