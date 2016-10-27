/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iscene.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:23:09 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/27 23:57:33 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ISCENE_H
# define ISCENE_H

# include "spot.h"

typedef enum	e_prim_type
{
	PLANE,
	SPHERE,
	CONE,
	CYLINDER,
	CUBE
}				t_prim_type;

typedef struct	s_itrans
{
	t_vec3		pos;
	t_vec3		rot_axis;
	float		rot_angle;
	t_vec3		scale;
}				t_itrans;

typedef struct	s_imaterial
{
	float		ambiant[3];
	float		diffuse[3];
	float		spec_intensity;
}				t_imaterial;

typedef struct	s_iprimitive
{
	t_prim_type	type;
	t_imaterial	mat;
	t_itrans	trans;
}				t_iprimitive;

typedef struct	s_iscene
{
	float			cam_pos[3];
	float			cam_dir[3];
	float			cam_up[3];
	int				camset;
	int				n_primitives;
	int				n_spots;
	t_iprimitive	*primitives;
	t_spot			*spots;
}				t_iscene;

int				scene_file_check(char *s, int size, unsigned long tsize);
t_iscene		*load_iscene(const char *fn);

#endif
