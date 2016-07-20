/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:21:58 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/19 23:22:33 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		PRIMITIVE_H
# define	PRIMITIVE_H

# include "rtv1.h"

typedef struct	s_primitive
{
	t_ray_intersect_fun intersect;
	t_mat4 model;
}				t_primitive;

#endif
