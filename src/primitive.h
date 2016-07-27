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

# include "rtv1.h"

typedef struct	s_primitive
{
	t_ray_intersect_fun intersect;
	t_vec3 pos;
	int diffuse;
}				t_primitive;

t_primitive *new_primitive(t_primitive *alloc, t_vec3 pos, int diffuse);

#endif
