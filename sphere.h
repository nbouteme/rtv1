/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:33:43 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/23 04:43:30 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		SPHERE_H
# define	SPHERE_H

#include "primitive.h"

typedef struct	s_sphere
{
	t_primitive base;
	float radius;
}				t_sphere;

t_primitive *new_sphere(t_sphere *self, float radius, t_vec3 pos, int color);

#endif
