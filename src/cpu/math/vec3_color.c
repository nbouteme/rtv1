/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 14:48:14 by nbouteme          #+#    #+#             */
/*   Updated: 2017/01/30 14:51:04 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cpu/math.h>

t_vec3 vec3_mix(t_vec3 a, t_vec3 b, float t)
{
	return (vec3_add(vec3_muls(a, (1.0f - t)), vec3_muls(b, t)));
}
