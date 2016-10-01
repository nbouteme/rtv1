/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 10:44:07 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 10:44:53 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT4_H
# define MAT4_H

# include <core/math_types/vec4.h>

struct			s_4dmat_named
{
	struct s_4dvec a;
	struct s_4dvec b;
	struct s_4dvec c;
	struct s_4dvec d;
};

typedef union	u_4dmat
{
	struct s_4dmat_named	n;
	struct s_4dvec			v[4];
}				t_4dmat;

typedef union	u_mat4
{
	t_4dmat		s;
	float		v[4][4];
}				t_mat4;

#endif
