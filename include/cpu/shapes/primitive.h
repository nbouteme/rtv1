/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:21:58 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/24 04:08:22 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		PRIMITIVE_H
# define	PRIMITIVE_H

# include <stdbool.h>
# include <cpu/math.h>
# include <core/ray.h>
# include <cpu/cpu_driver.h>

typedef struct	s_primitive t_primitive;
typedef bool (*t_ray_intersect_fun)(t_primitive *self,
									t_ray *ray,
									t_hit_info *hit);

typedef struct	s_primitive
{
	t_ray_intersect_fun intersect;
	t_mat4 transform;
	t_mat4 itransform;
	t_mat3 norm;
	t_mat3 inorm;
	t_vec3 diffuse;
	t_vec3 ambiant;
	float spec;
}				t_primitive;

t_primitive *new_primitive(t_primitive *alloc, t_iprimitive *base);
int intersect(t_primitive *self, t_ray *from, t_hit_info *info);

#endif
