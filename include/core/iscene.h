/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:23:09 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/19 23:24:00 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ISCENE_H
# define ISCENE_H

# include "spot.h"

typedef enum
{
	PLANE,
	SPHERE,
	CUBE
} t_prim_type;

typedef struct	s_iscene
{
	float cam_pos[3];
	float cam_dir[3];
	int n_primitives;
	int n_spots;
	t_prim_type *primitives;
	t_spot *spots;
}				t_iscene;

t_iscene *load_iscene(const char *fn);

#endif
