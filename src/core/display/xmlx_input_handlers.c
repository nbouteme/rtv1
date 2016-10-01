/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmlx_input_handlers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 11:20:45 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 12:25:43 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xmlx.h>
#include "xmlx_direct_disp.h"

void		handle_key(t_xmlx_window *self, int key, int act, int mods)
{
	t_display *d;

	(void)act;
	(void)mods;
	if (key == XMLX_KEY_ESCAPE)
		self->stop = true;
	d = register_display(0);
	if (d->key_handler)
		d->key_handler(d->renderer_driver->ctx, key);
}

void		handle_mouse(t_xmlx_window *self, double x, double y)
{
	t_display *d;

	(void)self;
	d = register_display(0);
	if (d->mouse_handler)
		d->mouse_handler(d->renderer_driver->ctx, x, y);
}

void		handle_mouse_button(t_xmlx_window *self, int button, int a, int m)
{
	t_display *d;

	(void)self;
	d = register_display(0);
	d->mouse_state = button;
	if (d->mouse_press_handler)
		d->mouse_press_handler(d->renderer_driver->ctx, button, a, m);
}
