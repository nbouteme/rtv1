/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mcpu_driver_functions.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 10:59:12 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 10:59:22 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MCPU_DRIVER_FUNCTIONS_H
# define MCPU_DRIVER_FUNCTIONS_H

# define HIDE_DRIVER_DEF
# include <core/driver_interface.h>
# undef HIDE_DRIVER_DEF

# ifndef SRC_CPU
#  error "This driver depends on the CPU driver"
# endif

void	mcpu_init(t_driver *self);
int		mcpu_genimage(t_display *disp);
void	mcpu_destroy(t_driver *self);

#endif
