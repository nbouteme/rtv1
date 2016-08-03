/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_driver.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:28:54 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/24 05:05:11 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		CPU_DRIVER_H
# define	CPU_DRIVER_H

# include "rtv1.h"
# include "display.h"
# include <xmlx.h>

void cpu_init(t_driver *self);
void cpu_genimage(t_driver *self, t_display *disp);
void cpu_destroy(t_driver *self);

typedef struct	s_cpudri_data
{
	t_mlx_ctx *mlx_ptr;
	t_xmlx_window *win_ptr;
	t_image *image;
	t_vec3 *fb;
}				t_cpudri_data;

typedef struct	s_driver
{
	t_driver_init			init;
	t_driver_genimage		genimage;
	t_driver_destroy		destroy;
	t_cpudri_data			*ctx;
	t_display_init_param	param;
}				t_driver;

#endif
