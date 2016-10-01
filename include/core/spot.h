/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spot.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:22:42 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 10:46:39 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPOT_H
# define SPOT_H

# include <core/core.h>

typedef struct	s_spot
{
	t_vec3 pos;
}				t_spot;

t_spot			*new_spot(t_spot *self, t_vec3 pos);

#endif
