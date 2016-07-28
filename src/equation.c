/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/24 02:32:15 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/28 02:39:02 by nbouteme         ###   ########.fr       */
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
		q = eq->b > 0 ?
			-0.5f * (eq->b + sqrt(discriminant)) :
			-0.5f * (eq->b - sqrt(discriminant));
		*eq->x0 = q / eq->a;
		*eq->x1 = eq->c / q;
	}
	if (*eq->x0 > *eq->x1)
	{
		q = *eq->x0;
		*eq->x0 = *eq->x1;
		*eq->x1 = q;
	}
	return (1);
}
