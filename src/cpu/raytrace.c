/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 12:42:37 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 14:10:10 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

#define MAXF(a, b) (a < b ? b : a)

int		inter(t_ray *from, t_scene *scene, t_hit_info *hit, t_inter_info *out)
{
	int			i;
	bool		hit_found;
	t_hit_info	back;

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
	spec = powf(MAXF(vec3_dot(args->ray->dir, refl), 0.0), args->prim->spec);
	specv = (t_vec3){{spec, spec, spec }};
	coef = coef < 0 ? 0.0 : coef;
	diff = vec3_muls(args->prim->diffuse, coef);
	return (vec3_add(vec3_add(specv, diff), args->prim->ambiant));
}

typedef t_inter_info	t_ii;

t_vec3	color_from_ray(t_scene *s, t_ray *from)
{
	int			i;
	t_hit_info	h[2];
	t_primitive	*p[2];
	t_ray		r;
	t_vec3		out[2];

	i = -1;
	ft_memset(&out[1], 0, sizeof(out[1]));
	ft_memset(p, 0, sizeof(p));
	if (!inter(from, s, &h[0], &(t_inter_info){9999, &p[0]}))
		return (vec3_null());
	while (++i < s->n_spots)
	{
		h[1] = h[0];
		p[1] = p[0];
		r = gen_ray(vec3_add(h[1].point,
			vec3_muls(h[1].normal, 0.001f)), s->spots[i].pos);
		out[0] = vec3_sub(s->spots[i].pos, h[1].point);
		if (inter(&r, s, &h[1], &(t_ii){vec3_norme(out[0]), &p[1]}))
			out[1] = vec3_add(out[1], p[0]->ambiant);
		else
			out[1] = vec3_add(out[1], color_from_material(&(t_colargs) {
				s, from, p[0], &h[1], r, out[0]}));
	}
	return (vec3_muls(out[1], 1.0f / s->n_spots));
}
