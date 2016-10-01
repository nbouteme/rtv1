/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmlx_direct_disp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 11:17:39 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 12:25:10 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xmlx_direct_disp.h"

static void	draw_loop_xmlx(t_display *d)
{
	t_xmlx_disp_data *dd;

	dd = d->disp_internal;
	dd->win_ptr->stop = d->renderer_driver->genimage(d);
	xmlx_draw(dd->win_ptr);
}

static int	gen_xmlx(t_display *d)
{
	t_xmlx_disp_data *dd;

	dd = d->disp_internal;
	if (dd->win_ptr->stop)
		return (false);
	xmlx_run_window(dd->win_ptr, draw_loop_xmlx, d);
	return (true);
}

void		init_dir_xmlx(t_display *d)
{
	t_xmlx_disp_data *disp_int;

	disp_int = malloc(sizeof(*disp_int));
	disp_int->mlx_ptr = xmlx_init();
	disp_int->win_ptr = xmlx_new_window(d->param.x, d->param.y,
										"rt", FLOAT4);
	disp_int->win_ptr->on_key = handle_key;
	disp_int->win_ptr->on_mouse_move = handle_mouse;
	disp_int->win_ptr->on_mouse_button = handle_mouse_button;
	disp_int->image = disp_int->win_ptr->framebuffer;
	disp_int->fb = (t_vec3*)disp_int->image->buffer;
	xmlx_present(disp_int->win_ptr);
	d->disp_internal = disp_int;
	d->disp_param = (void*)(long)disp_int->win_ptr->framebuffer->tex_id;
	if (d->renderer_driver->init)
		d->renderer_driver->init(d);
}

void		init_xmlx_dir(t_display *d)
{
	d->init = init_dir_xmlx;
	d->draw = gen_xmlx;
	d->fini = close_xmlx;
}
