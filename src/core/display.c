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

#include <core/core.h>

void init_display(t_display *ret, t_display_interface d)
{
	const t_disp_init_f displays[] = {init_xmlx, init_png, init_xmlx_dir};

	ret->type = d;
	displays[d](ret);
}

t_display *new_display(t_display_init_param params)
{
	t_display *ret;

	ret = ft_memalloc(sizeof(*ret));
	ret->param = params;
	ret->renderer_driver = get_driver(params.type, params.display_type);
	if (!ret->renderer_driver)
	{
		free(ret);
		ft_putendl("Specified backend cannot use the specified display mode");
		return (0);
	}
	ret->user_ptr = params.user_ptr;
	ret->renderer_driver->param = params;
	init_display(ret, params.display_type);
	return (ret);
}

void run_display(t_display *disp)
{
	if (disp->init)
		disp->init(disp);
	while (disp->draw(disp))
		;
	if (disp->fini)
		disp->fini(disp);
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
