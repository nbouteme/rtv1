/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/24 02:15:54 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 10:45:49 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

typedef struct	s_3dvec
{
	float x;
	float y;
	float z;
}				t_3dvec;

union			u_vec3
{
	struct s_3dvec	s;
	float			v[3];
} __attribute__((__transparent_union__));

typedef union u_vec3	t_vec3;

#endif
