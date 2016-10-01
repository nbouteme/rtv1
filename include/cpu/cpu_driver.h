/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_driver.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:28:54 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 10:47:29 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPU_DRIVER_H
# define CPU_DRIVER_H

# define HIDE_DRIVER_DEF
# include <core/driver_interface.h>
# undef HIDE_DRIVER_DEF

typedef struct	s_driver
{
	t_driver_init			init;
	t_driver_genimage		genimage;
	t_driver_destroy		destroy;
	void					*ctx;
	t_display_init_param	param;
}				t_driver;

typedef struct	s_hit_info
{
	t_vec3	point;
	t_vec3	normal;
	float	dist;
}				t_hit_info;

#endif
