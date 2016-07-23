/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 00:19:26 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/23 04:26:05 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "primitive.h"

t_primitive *new_primitive(t_primitive *alloc, t_vec3 pos, int diffuse)
{
	(void) pos;
	alloc->diffuse = diffuse;
	/* TODO: creer matrice */
	return (alloc);
}
