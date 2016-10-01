/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_display.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 11:15:55 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 13:37:36 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XMLX_DIRECT_DISP_H
# define XMLX_DIRECT_DISP_H

# include <core/core.h>
# include <xmlx.h>

void			handle_key(t_xmlx_window *self, int key, int act, int mods);
void			close_xmlx(t_display *d);
void			handle_mouse_button(t_xmlx_window *self, int b, int a, int m);
void			handle_mouse(t_xmlx_window *self, double x, double y);
void			init_xmlx_dir(t_display *d);

typedef struct	s_xmlx_disp_data
{
	t_mlx_ctx		*mlx_ptr;
	t_xmlx_window	*win_ptr;
	t_image			*image;
	t_vec3			*fb;
}				t_xmlx_disp_data;

#endif
