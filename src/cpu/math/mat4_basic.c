/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_basic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 12:46:53 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 13:03:08 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cpu/math.h>

t_mat4	mat4_ident(void)
{
	t_mat4		ret;
	unsigned	i;

	ft_memset(&ret, 0, sizeof(ret));
	i = ~0;
	while (++i < 4)
		ret.v[i][i] = 1.0f;
	return (ret);
}

t_mat4	mat4_mult(t_mat4 a, t_mat4 b)
{
	t_mat4	c;
	int		i;
	int		j;
	int		k;

	i = 0;
	ft_memset(&c, 0, sizeof(c));
	while (i < 4)
	{
		k = 0;
		while (k < 4)
		{
			j = 0;
			while (j < 4)
			{
				c.v[i][j] += a.v[i][k] * b.v[k][j];
				++j;
			}
			++k;
		}
		++i;
	}
	return (c);
}

t_mat4	mat4_muls(t_mat4 a, float b)
{
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			a.v[i][j] *= b;
			++j;
		}
		++i;
	}
	return (a);
}
