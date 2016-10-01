/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 10:33:04 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 10:43:12 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT3_H
# define MAT3_H

# include <core/math_types/vec3.h>

# define DAM union {

struct				s_3dmat_named
{
	struct s_3dvec	a;
	struct s_3dvec	b;
	struct s_3dvec	c;
};

typedef union		u_3dmat
{
	struct s_3dmat_named	n;
	struct s_3dvec			v[3];
}					t_3dmat;

typedef union		u_mat3
{
	t_3dmat			s;
	float			v[3][3];
}					t_mat3;

#endif
