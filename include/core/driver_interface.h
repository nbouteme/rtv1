/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver_interface.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 10:27:39 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 10:28:40 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRIVER_INTERFACE_H
# define DRIVER_INTERFACE_H

# include <core/display.h>
# include <core/core.h>

typedef struct s_driver		t_driver;
typedef struct s_display	t_display;

typedef void				(*t_driver_init)(t_display *self);
typedef int					(*t_driver_genimage)(t_display *disp);
typedef void				(*t_driver_destroy)(t_display *self);

t_driver					*get_driver(t_display_type type,
										t_display_interface dt);

# ifndef HIDE_DRIVER_DEF

struct						s_driver
{
	t_driver_init			init;
	t_driver_genimage		genimage;
	t_driver_destroy		destroy;
	void					*ctx;
	t_display_init_param	param;
};

# endif

#endif
