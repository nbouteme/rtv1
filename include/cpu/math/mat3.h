/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 10:48:43 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 10:48:53 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT3_H
# define MAT3_H

# include <core/math_types.h>

float	mat3_det(t_mat3 m);
t_mat3	mat3_transpose(t_mat3 m);
t_mat3	mat3_inverse(t_mat3 m);
t_mat3	mat3_topleft(t_mat4 m);
t_vec3	mat3_transform3(t_mat3 m, t_vec3 a);
t_mat3	mat3_add(t_mat3 a, t_mat3 b);
t_mat3	mat3_muls(t_mat3 a, float b);
t_mat3	mat3_mult(t_mat3 a, t_mat3 b);
t_mat3	mat3_ident();

#endif
