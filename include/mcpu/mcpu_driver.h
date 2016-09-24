/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mcpu_driver.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:28:54 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/24 04:46:28 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MCPU_DRIVER_H
# define MCPU_DRIVER_H

# define HIDE_DRIVER_DEF
# include <core/driver_interface.h>
# undef HIDE_DRIVER_DEF

# include <xmlx.h>

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

typedef struct	s_hit_info
{
	t_vec3 point;
	t_vec3 normal;
	float dist;
}				t_hit_info;

#endif
