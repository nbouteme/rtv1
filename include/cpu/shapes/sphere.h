/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:33:43 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 10:57:05 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "primitive.h"

typedef struct	s_sphere
{
	t_primitive base;
	float		radius;
	float		radius2;
}				t_sphere;

t_primitive		*new_sphere(t_sphere *s, float r, t_vec3 p, t_vec3 c);
bool			sphere_ray_intersect(t_primitive *b, t_ray *r, t_hit_info *o);

#endif
