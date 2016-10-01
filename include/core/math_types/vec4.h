/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/24 02:15:54 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 10:46:14 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC4_H
# define VEC4_H

typedef struct	s_4dvec
{
	float x;
	float y;
	float z;
	float w;
}				t_4dvec;

union			u_vec4
{
	struct s_4dvec	s;
	float			v[4];
} __attribute__((__transparent_union__));

typedef union u_vec4	t_vec4;

#endif
