/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:33:43 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/19 23:34:08 by nbouteme         ###   ########.fr       */
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

t_primitive *new_sphere(float radius, t_vec3 pos);

#endif
