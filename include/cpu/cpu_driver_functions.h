/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_driver_functions.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 10:47:34 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 10:47:43 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPU_DRIVER_FUNCTIONS_H
# define CPU_DRIVER_FUNCTIONS_H

# define HIDE_DRIVER_DEF
# include <core/driver_interface.h>
# undef HIDE_DRIVER_DEF

void	cpu_init(t_driver *self);
int		cpu_genimage(t_display *disp);
void	cpu_destroy(t_driver *self);

#endif
