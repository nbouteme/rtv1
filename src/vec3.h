/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/24 02:15:54 by nbouteme          #+#    #+#             */
/*   Updated: 2016/08/01 23:10:13 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		VEC3_H
# define	VEC3_H

float vec3_norme(t_vec3 v);
t_vec3 rotate_dir(float u, float v, t_vec3 dir);
t_vec3 vec3_muls(t_vec3 v, float s);
t_vec3 vec3_add(t_vec3 a, t_vec3 b);
t_vec3 vec3_sub(t_vec3 a, t_vec3 b);
t_vec3 vec3_cross(t_vec3 a, t_vec3 b);
void vec3_normalize(t_vec3 a);
float vec3_dot(t_vec3 a, t_vec3 b);

#endif
