
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

#ifndef		CONE_H
# define	CONE_H

#include "primitive.h"

typedef struct	s_cone
{
	t_primitive base;
	float radius;
	float radius2;
}				t_cone;

t_primitive *new_cone(t_cone *self, t_mat4 trans, t_vec3 color);
bool cone_ray_intersect(t_primitive *base, t_ray *ray, t_hit_info *out);

#endif
