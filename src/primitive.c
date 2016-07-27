/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 00:19:26 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/24 04:08:46 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "primitive.h"

t_primitive *new_primitive(t_primitive *alloc, t_vec3 pos, int diffuse)
{
	ft_memcpy(alloc->pos, pos, sizeof(float[3]));
	alloc->diffuse = diffuse;
	/* TODO: creer matrice */
	return (alloc);
}
