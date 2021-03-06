/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:19:55 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 10:46:25 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include <core/math_types.h>

typedef struct	s_ray
{
	t_vec3 pos;
	t_vec3 dir;
}				t_ray;

#endif
