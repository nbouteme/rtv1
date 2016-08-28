
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:33:43 by nbouteme          #+#    #+#             */
/*   Updated: 2016/08/14 01:30:24 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		CYLINDER_H
# define	CYLINDER_H

#include "primitive.h"

typedef struct	s_cylinder
{
	t_primitive base;
	float radius;
	float radius2;
}				t_cylinder;

t_primitive *new_cylinder(t_cylinder *self, t_mat4 trans, t_vec3 color);
bool cylinder_ray_intersect(t_primitive *base, t_ray *ray, t_hit_info *out);

#endif
