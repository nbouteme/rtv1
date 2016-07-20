/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:32:13 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/20 23:56:23 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

t_display *new_display(int x, int y)
{
	t_display *ret;

	ret = malloc(sizeof(*ret));
	ret->ctx.mlx = mlx_init();
	ret->ctx.win = mlx_new_window(ret->ctx.mlx, x, y, "RTV1");
}
