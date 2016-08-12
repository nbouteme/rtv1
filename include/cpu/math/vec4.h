/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/24 02:15:54 by nbouteme          #+#    #+#             */
/*   Updated: 2016/08/10 02:11:49 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		VEC4_H
# define	VEC4_H

# include <core/math_types.h>

float vec4_norme(t_vec4 v);
t_vec4 vec4_muls(t_vec4 v, float s);
t_vec4 vec4_mul(t_vec4 a, t_vec4 b);
t_vec4 vec4_add(t_vec4 a, t_vec4 b);
t_vec4 vec4_sub(t_vec4 a, t_vec4 b);
t_vec4 vec4_div(t_vec4 a, t_vec4 b);
t_vec4 vec4_cross(t_vec4 a, t_vec4 b);
void vec4_normalize(t_vec4 *a);
float vec4_dot(t_vec4 a, t_vec4 b);
t_vec4 vec4_null();

#endif
