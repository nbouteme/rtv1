/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 01:05:21 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 10:54:31 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "primitive.h"

typedef struct	s_plane
{
	t_primitive	base;
	t_vec3		normal;
	t_vec3		center;
}				t_plane;

t_primitive		*new_plane(t_plane *plane, t_mat4 trans, t_vec3 color);
bool			plane_ray_intersect(t_primitive *b, t_ray *r, t_hit_info *o);

#endif
