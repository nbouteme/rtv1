/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_driver_functions.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 10:58:06 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 10:58:16 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUDA_DRIVER_FUNCTIONS_H
# define CUDA_DRIVER_FUNCTIONS_H

# define HIDE_DRIVER_DEF
# include <core/driver_interface.h>
# undef HIDE_DRIVER_DEF

void	cuda_init(t_display *self);
int		cuda_genimage(t_display *disp);
void	cuda_fini(t_display *self);

#endif
