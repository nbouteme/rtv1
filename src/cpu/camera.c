/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 12:39:34 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 14:10:22 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

void	bake_camray(t_camera *c)
{
	t_vec3 lap;

	c->vphw = tan(M_PI / 8);
	c->vphh = (720.0f / 1280.0f) * c->vphw;
	lap = vec3_add(c->pos, c->dir);
	c->u = vec3_cross(c->up, c->dir);
	c->v = vec3_cross(c->dir, c->u);
	vec3_normalize(&c->u);
	vec3_normalize(&c->v);
	c->vpblp = vec3_sub(lap, vec3_sub(vec3_muls(c->v, c->vphh),
									vec3_muls(c->u, c->vphw)));
	c->v = vec3_muls(c->v, c->vphh * 2.0f / 720.0f);
	c->u = vec3_muls(c->u, c->vphw * 2.0f / 1280.0f);
}

t_ray	gen_ray(t_vec3 from, t_vec3 to)
{
	t_ray ret;

	ret.dir = vec3_sub(to, from);
	vec3_normalize(&ret.dir);
	ret.pos = from;
	return (ret);
}

t_ray	gen_camray(int x, int y, t_camera *c)
{
	return (gen_ray(c->pos, vec3_add(c->vpblp, vec3_add(vec3_muls(c->v, y),
														vec3_muls(c->u, -x)))));
}

float	conv(float c)
{
	if (c < 0.0031308f)
		return (12.92f * c);
	return (1.055f * powf(c, 0.4166667) - 0.055f);
}

void	correct_gamma(t_vec3 *framebuffer)
{
	const int	pixs = 720 * 1280;
	int			i;

	i = -1;
	while (++i < pixs)
		framebuffer[i].s = (t_3dvec)
			{
				conv(framebuffer[i].s.x),
				conv(framebuffer[i].s.y),
				conv(framebuffer[i].s.z)
			};
}
