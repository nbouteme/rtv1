/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/24 02:15:54 by nbouteme          #+#    #+#             */
/*   Updated: 2017/01/30 14:45:22 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include <core/math_types.h>

float	vec3_norme(t_vec3 v);
float	vec3_dot(t_vec3 a, t_vec3 b);
void	vec3_normalize(t_vec3 *a);
t_vec3	vec3_muls(t_vec3 v, float s);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_div(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
t_vec3	vec3_null();
t_vec3	vec3_reflect(t_vec3 i, t_vec3 n);
t_vec3	vec3_mix(t_vec3 a, t_vec3 b, float t);

#endif
