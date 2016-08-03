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

#ifndef		SCENE_H
# define	SCENE_H

#include "rtv1.h"
#include "primitive.h"
#include "spot.h"

typedef struct	s_scene
{
	t_vec3 cam_pos;
	t_vec3 cam_dir;
	int n_primitives;
	int n_spots;
	t_primitive **primitives;
	t_spot *spots;
}				t_scene;

t_scene *load_scene(const char *fn);

#endif
