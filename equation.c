/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/24 02:32:15 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/24 04:11:47 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "equation.h"

int solve_second(t_sec_equation *eq)
{
	float discriminant;
	float q;

	discriminant = eq->b * eq->b - 4 * eq->a * eq->c;
	if (discriminant < 0)
		return (0);
	if (discriminant == 0)
	{
		*eq->x0 = -0.5f * (eq->b / eq->a);
		*eq->x1 = *eq->x0;
	}
	else
	{
		q = eq->b;
		q += sqrt(discriminant) * (eq->b > 0 ? 1.0f : -1.0f);
		q *= -0.5f;
		*eq->x0 = q / eq->a;
		*eq->x1 = eq->c / q;
	}
	return (1);
}
