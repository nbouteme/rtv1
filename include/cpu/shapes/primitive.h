/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:21:58 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 10:56:08 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIMITIVE_H
# define PRIMITIVE_H

# include <stdbool.h>
# include <cpu/math.h>
# include <core/ray.h>
# include <cpu/cpu_driver.h>

typedef struct s_primitive	t_primitive;
typedef bool	(*t_ray_intersect_fun)(t_primitive *self,
									t_ray *ray,
									t_hit_info *hit);

struct						s_primitive
{
	t_ray_intersect_fun	intersect;
	t_mat4				transform;
	t_mat4				itransform;
	t_mat3				norm;
	t_mat3				inorm;
	t_vec3				diffuse;
	t_vec3				ambiant;
	float				spec;
};

t_primitive					*new_primitive(t_primitive *a, t_iprimitive *b);
int							intersect(t_primitive *s, t_ray *f, t_hit_info *i);

#endif
