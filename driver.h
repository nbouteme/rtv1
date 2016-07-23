/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 23:24:34 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/23 02:05:07 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		DRIVER_H
# define	DRIVER_H

#include "rtv1.h"
#include "display.h"

typedef struct	s_driver
{
	t_driver_init			init;
	t_driver_genimage		genimage;
	t_driver_destroy		destroy;
	void					*ctx;
	t_display_init_param	param;
}				t_driver;

#endif
