/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:32:13 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/23 02:51:05 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "driver.h"

t_display *new_display(t_display_init_param params)
{
	t_display *ret;

	ret = ft_memalloc(sizeof(*ret));
	ret->renderer_driver = get_driver(params.type);
	ret->user_ptr = params.user_ptr;
	ret->renderer_driver->param = params;
	return (ret);
}

void run_display(t_display *disp)
{
	disp->renderer_driver->init(disp->renderer_driver);
	disp->renderer_driver->genimage(disp->renderer_driver, disp);
	disp->renderer_driver->destroy(disp->renderer_driver);
}

t_display *register_display(t_display *d)
{
	static t_display *display = 0;

	if (d)
		display = d;
	return (display);
}

void end_application()
{
	t_display *display = register_display(0);
	(void)display;
	exit(1);
}
