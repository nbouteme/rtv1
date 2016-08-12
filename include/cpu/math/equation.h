/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/24 02:32:55 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/24 04:11:44 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		EQUATION_H
# define	EQUATION_H

# include <cpu/math.h>

typedef struct
{
	float a;
	float b;
	float c;
	float *x0;
	float *x1;
}		t_sec_equation;

int solve_second(t_sec_equation *eq);

#endif
