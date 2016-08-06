/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 01:05:21 by nbouteme          #+#    #+#             */
/*   Updated: 2016/08/06 00:42:04 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
#define PLANE_H

#include "primitive.h"
typedef struct	s_plane
{
	t_primitive base;
}				t_plane;
t_primitive *new_plane(t_plane *plane, t_mat4 trans, t_vec3 color);

#endif
